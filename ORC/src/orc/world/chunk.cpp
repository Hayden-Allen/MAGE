#include "pch.h"
#include "chunk.h"
#include "sprite_batch.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	chunk::chunk(const glm::uvec2& pos) :
		mage::chunk_base<sprite_batch>(pos),
		m_tile_count(0),
		m_grid{ 0 }
	{}
	chunk::chunk(sprite_batch_bank& sbb, coga::input_file& in) :
		mage::chunk_base<sprite_batch>({ 0, 0 }),
		m_tile_count(0),
		m_grid{ 0 }
	{
		load(sbb, in);
	}



	void chunk::save(coga::output_file& out) const
	{
		mage::chunk_base<sprite_batch>::save(out);

		out.ulong(m_batches.size());
		for (const auto& batch : m_batches)
			out.uint(batch->get_handle());

		out.ulong(m_tile_count);
		out.write(m_grid, mage::c::tiles_per_chunk);

		const size_t layer_count = m_tile_offsets.size();
		out.ulong(layer_count);
		for(const auto& layer : m_tile_offsets)
		{
			// layer index
			out.ulong(layer.first);
			const size_t row_count = layer.second.size();
			// number of y coords
			out.ulong(row_count);
			for (const auto& row : layer.second)
			{
				// y coord
				out.ulong(row.first);
				// number of x coords in current row
				out.ulong(row.second.size());
				for (const auto& col : row.second)
				{
					// x coord
					out.ulong(col.first);
					// sprite_batch handle
					out.uint(col.second.first);
					// offset in VBO
					out.ulong(col.second.second);
				}
			}
		}
	}
	void chunk::load(sprite_batch_bank& sbb, coga::input_file& in)
	{
		load(in);
		
		const size_t batch_count = in.ulong();
		m_batches.reserve(batch_count);
		for (size_t i = 0; i < batch_count; i++)
			m_batches.push_back(sbb.get(in.uint()));
		
		m_tile_count = in.ulong();
		in.read(m_grid, mage::c::tiles_per_chunk);

		const size_t layer_count = in.ulong();
		m_tile_offsets.reserve(layer_count);
		for(size_t i = 0; i < layer_count; i++)
		{
			const size_t layer = in.ulong();
			const size_t row_count = in.ulong();
			std::unordered_map<size_t, std::unordered_map<size_t, std::pair<sprite_batch_bank::handle, size_t>>> row;
			row.reserve(row_count);
			for (size_t j = 0; j < row_count; j++)
			{
				const size_t y = in.ulong();
				const size_t col_count = in.ulong();
				std::unordered_map<size_t, std::pair<sprite_batch_bank::handle, size_t>> col;
				col.reserve(col_count);
				for (size_t k = 0; k < col_count; k++)
				{
					const size_t x = in.ulong();
					const sprite_batch_bank::handle h = in.uint();
					const size_t off = in.ulong();
					col.insert({ x, { h, off } });
				}
				row.insert({ y, col });
			}
			m_tile_offsets.insert({ layer, row });
		}
	}
	void chunk::set_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer, sprite* const sprite)
	{
		// done by map::set_tile_at
		// set_grid(pos, layer, sprite, true);
		// only the root tile should have this index (others should be placeholders)
		m_grid[get_index(pos, layer)] = sprite->get_handle();
		m_tile_count++;

		sprite_batch* added_to = nullptr;
		size_t offset = 0;
		mage::tile t =
		{
			sprite->get_handle(),
			{
				{ COGA_CAST(uint8_t, pos.x), COGA_CAST(uint8_t, pos.y) },
				{
					COGA_CAST(uint8_t, pos.x + sprite->get_tile_w()),
					COGA_CAST(uint8_t, pos.y + sprite->get_tile_h())
				}
			}
		};

		// attempt to add to an existing batch
		bool added = false;
		for (auto& batch : m_batches)
		{
			if (added = batch->can_contain(sprite))
			{
				offset = batch->add_tile(sb, t);
				added_to = batch;
				break;
			}
		}

		// no room in existing batches, make a new batch
		if (!added)
		{
			added_to = new sprite_batch(sbb, m_coords);
			COGA_ASSERT(added_to->can_contain(sprite), "Invalid tile");
			offset = added_to->add_tile(sb, t);
			m_batches.push_back(added_to);
		}

		// store new tile's index in the batch's VBO (necessary for deletion)
		if (!m_tile_offsets[layer].contains(pos.y))
			m_tile_offsets[layer].insert({ pos.y, {} });
		if (!m_tile_offsets[layer][pos.y].contains(pos.x))
			m_tile_offsets[layer][pos.y].insert({ pos.x, { 0, 0 } });
		// account for NxN tiles
		for(size_t i = pos.y; i < pos.y + sprite->get_tile_h(); i++)
			for(size_t j = pos.x; j < pos.x + sprite->get_tile_w(); j++)
				m_tile_offsets[layer][i][j] = { added_to->get_handle(), offset };
	}
	void chunk::delete_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer)
	{
		const sprite_bank::handle old = m_grid[get_index(pos, layer)];
		const auto& pair = m_tile_offsets[layer][pos.y][pos.x];
		const auto& batch = sbb.get(pair.first);
		const sprite* const sprite = sb.get(old);
		batch->delete_tile(sprite, pair.second);
		// TODO properly
		if (batch->is_empty())
			m_batches.erase(std::find(m_batches.begin(), m_batches.end(), batch));

		// account for NxN tiles
		for (size_t i = pos.y; i < pos.y + sprite->get_tile_h(); i++)
		{
			for (size_t j = pos.x; j < pos.x + sprite->get_tile_w(); j++)
				m_tile_offsets[layer][i].erase(j);
			if (m_tile_offsets[layer][i].empty())
				m_tile_offsets[layer].erase(i);
		}
		if (m_tile_offsets[layer].empty())
			m_tile_offsets.erase(layer);
	}
	sprite_bank::handle chunk::get_tile_at(const glm::uvec2& pos, size_t layer) const
	{
		return m_grid[get_index(pos, layer)];
	}



	size_t chunk::get_index(const glm::uvec2& pos, size_t layer)
	{
		COGA_ASSERT(pos.x < mage::c::tiles_per_chunk_side && pos.y < mage::c::tiles_per_chunk_side, "Invalid chunk coordinates <{}, {}>", pos.x, pos.y);
		COGA_ASSERT(layer < mage::c::layers_per_chunk, "Invalid chunk layer {}", layer);

		return (layer * mage::c::tiles_per_chunk_layer) + (pos.y * mage::c::tiles_per_chunk_side) + pos.x;
	}
	//void chunk::set_grid(const glm::uvec2& pos, size_t layer, const sprite* const s, bool add)
	//{
	//	for (size_t i = pos.y; i < MAGE_CAST(size_t, pos.y) + s->get_tile_h(); i++)
	//	{
	//		for (size_t j = pos.x; j < MAGE_CAST(size_t, pos.x) + s->get_tile_w(); j++)
	//		{
	//			// other chunks must handle this themselves
	//			if (i >= mage::c::tiles_per_chunk_side || j >= mage::c::tiles_per_chunk_side)
	//				continue;
	//			// If adding, set only the root tile to the sprite's index and make the rest placeholders. If deleting, set all to invalid.
	//			const sprite_bank::handle index = (add ? ((i == pos.y && j == pos.x) ? s->get_handle() : sprite_bank::s_placeholder) : sprite_bank::s_invalid);
	//			m_grid[get_index({ j, i }, layer)] = index;
	//			COGA_TRACE("<{}, {}> => {}", j, i, index);
	//		}
	//	}
	//}
	/*void chunk::fill_grid(const glm::uvec2& pos, const glm::uvec2& dim, size_t layer, sprite_bank::handle h)
	{
		for (size_t i = pos.y; i < MAGE_CAST(size_t, pos.y) + dim.y; i++)
			for (size_t j = pos.x; j < MAGE_CAST(size_t, pos.x) + dim.x; j++)
			{
				COGA_ASSERT(j < mage::c::tiles_per_chunk_side&& i < mage::c::tiles_per_chunk_side, "Invalid dims");
				m_grid[get_index({ j, i }, layer)] = h;
			}
	}*/
}
