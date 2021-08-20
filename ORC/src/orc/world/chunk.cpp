#include "pch.h"
#include "chunk.h"
#include "sprite_batch.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	chunk::chunk(const glm::uvec2& pos) :
		n::chunk_base<sprite_batch>(pos),
		m_tile_count(0),
		m_grid{ 0 }
	{}
	chunk::chunk(sprite_batch_bank& sbb, mage::input_file& in) :
		n::chunk_base<sprite_batch>({ 0, 0 }),
		m_tile_count(0),
		m_grid{ 0 }
	{
		load(sbb, in);
	}



	void chunk::save(mage::output_file& out) const
	{
		n::chunk_base<sprite_batch>::save(out);

		out.ulong(m_batches.size());
		for (const auto& batch : m_batches)
			out.uint(batch->get_handle());

		out.ulong(m_tile_count);
		out.write(m_grid, n::c::tiles_per_chunk);

		const size_t row_count = m_tile_offsets.size();
		// number of y coords
		out.ulong(row_count);
		for (const auto& row : m_tile_offsets)
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
	void chunk::load(sprite_batch_bank& sbb, mage::input_file& in)
	{
		load(in);
		
		const size_t batch_count = in.ulong();
		m_batches.reserve(batch_count);
		for (size_t i = 0; i < batch_count; i++)
			m_batches.push_back(sbb.get(in.uint()));
		
		m_tile_count = in.ulong();
		in.read(m_grid, n::c::tiles_per_chunk);

		const size_t row_count = in.ulong();
		m_tile_offsets.reserve(row_count);
		for (size_t i = 0; i < row_count; i++)
		{
			const size_t y = in.ulong();
			const size_t col_count = in.ulong();
			std::unordered_map<size_t, std::pair<sprite_batch_bank::handle, size_t>> col;
			col.reserve(col_count);
			for (size_t j = 0; j < col_count; j++)
			{
				const size_t x = in.ulong();
				const sprite_batch_bank::handle h = in.uint();
				const size_t off = in.ulong();
				col.insert({ x, { h, off } });
			}
			m_tile_offsets.insert({ y, col });
		}
	}
	void chunk::set_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer, sprite* const sprite)
	{
		const size_t index = get_index(pos, layer);
		if (m_grid[index] == sprite->get_handle())
			return;

		m_grid[index] = sprite->get_handle();
		m_tile_count++;

		sprite_batch* added_to = nullptr;
		size_t offset = 0;
		n::tile t =
		{
			sprite->get_handle(),
			{
				{ pos.x, pos.y },
				{
					N_CAST(uint8_t, pos.x + sprite->get_w() / n::c::pixels_per_sprite_side),
					N_CAST(uint8_t, pos.y + sprite->get_h() / n::c::pixels_per_sprite_side)
				}
			}
		};
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
			MAGE_ASSERT(added_to->can_contain(sprite), "Invalid tile");
			offset = added_to->add_tile(sb, t);
			m_batches.push_back(added_to);
		}

		// store new tile's index in the batch's VBO
		if (!m_tile_offsets.contains(pos.y))
			m_tile_offsets.insert({ pos.y, {} });
		if (!m_tile_offsets[pos.y].contains(pos.x))
			m_tile_offsets[pos.y].insert({ pos.x, { 0, 0 } });
		m_tile_offsets[pos.y][pos.x] = { added_to->get_handle(), offset };
	}
	void chunk::delete_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer)
	{
		const size_t index = get_index(pos, layer);
		if (m_grid[index] == sprite_bank::s_invalid)
			return;

		const sprite_bank::handle old = m_grid[index];
		// delete given tile from the batch that contains it
		m_grid[index] = sprite_bank::s_invalid;
		const auto& pair = m_tile_offsets[pos.y][pos.x];
		const auto& batch = sbb.get(pair.first);
		batch->delete_tile(sb.get(old), pair.second);
		// TODO properly
		if (batch->is_empty())
			m_batches.erase(std::find(m_batches.begin(), m_batches.end(), batch));

		// remove given tile's record, because it no longer exists
		m_tile_offsets[pos.y].erase(pos.x);
		if (m_tile_offsets[pos.y].size() == 0)
			m_tile_offsets.erase(pos.y);
	}
}
