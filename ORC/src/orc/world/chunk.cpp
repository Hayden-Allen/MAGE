#include "pch.h"
#include "chunk.h"
#include "sprite_batch.h"
#include "sprite_batch_constructor.h"

namespace orc
{
	chunk::chunk(const glm::uvec2& pos) :
		n::chunk(pos),
		m_tile_count(0),
		m_grid{ 0 }
	{}
	chunk::chunk(mage::input_file& in) :
		n::chunk({ 0, 0 }),
		m_tile_count(0),
		m_grid{ 0 }
	{
		load(in);
	}



	void chunk::save(mage::output_file& out) const
	{
		n::chunk::save(out);
		out.ulong(m_tile_count);
		out.write(m_grid, n::c::tiles_per_chunk);

		// TODO need sprite_batch_bank so this can be serialized
		/*const size_t row_count = m_tile_offsets.size();
		out.ulong(row_count);
		for (const auto& row : m_tile_offsets)
		{
			const size_t tile_count = row.second.size();
			out.ulong(tile_count);
			for (const auto& pair : row.second)
			{
				out.ulong(pair.)
			}
		}*/
	}
	void chunk::load(mage::input_file& in)
	{
		// TODO cleanup
		// this has to be rewritten here because n::chunk::load instantiates n::sprite_batches, but orc::chunk::load needs to instantiate orc::sprite_batches
		m_coords.x = in.uint();
		m_coords.y = in.uint();

		const size_t batch_count = in.ulong();
		m_batches.reserve(batch_count);
		for (size_t i = 0; i < batch_count; i++)
			m_batches.push_back(new sprite_batch(in));

		m_tile_count = in.ulong();
		in.read(m_grid, n::c::tiles_per_chunk);
	}
	void chunk::set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite)
	{
		MAGE_ASSERT(pos.x < n::c::tiles_per_chunk_side&& pos.y < n::c::tiles_per_chunk_side, "Invalid chunk coordinates <{}, {}>", pos.x, pos.y);
		MAGE_ASSERT(layer < n::c::layers_per_chunk, "Invalid chunk layer {}", layer);


		const size_t index = (layer * n::c::tiles_per_chunk_layer) + (pos.y * n::c::tiles_per_chunk_side) + pos.x;
		if (m_grid[index] == sprite->get_handle())
			return;

		m_grid[index] = sprite->get_handle();
		m_tile_count++;


		n::sprite_batch_base* added_to = nullptr;
		size_t offset = 0;
		n::tile t =
		{
			sprite,
			{
				{ 1.f * pos.x, 1.f * pos.y },
				{
					1.f * pos.x + 1.f * sprite->get_w() / n::c::pixels_per_sprite_side,
					1.f * pos.y + 1.f * sprite->get_h() / n::c::pixels_per_sprite_side
				}
			}
		};
		bool added = false;
		for (auto& batch : m_batches)
		{
			// TODO
			if (added = batch->can_contain(sprite))
			{
				offset = batch->add_tile(t);
				added_to = batch;
				break;
			}
		}

		// no room in existing batches, make a new batch
		if (!added)
		{
			added_to = new sprite_batch(m_coords);
			MAGE_ASSERT(added_to->can_contain(t.sprite), "Invalid tile");
			offset = added_to->add_tile(t);
			m_batches.push_back(added_to);
			MAGE_INFO("CREATE SB");
		}

		// store new tile's index in the batch's VBO
		if (!m_tile_offsets.contains(pos.y))
			m_tile_offsets.insert({ pos.y, {} });
		if (!m_tile_offsets[pos.y].contains(pos.x))
			m_tile_offsets[pos.y].insert({ pos.x, { nullptr, 0 } });
		m_tile_offsets[pos.y][pos.x] = { added_to, offset };
	}
	void chunk::delete_tile_at(const glm::uvec2& pos, size_t layer)
	{
		// TODO abstract into base method
		MAGE_ASSERT(pos.x < n::c::tiles_per_chunk_side&& pos.y < n::c::tiles_per_chunk_side, "Invalid chunk coordinates <{}, {}>", pos.x, pos.y);
		MAGE_ASSERT(layer < n::c::layers_per_chunk, "Invalid chunk layer {}", layer);


		const size_t index = (layer * n::c::tiles_per_chunk_layer) + (pos.y * n::c::tiles_per_chunk_side) + pos.x;
		if (m_grid[index] == n::sprite_bank::s_invalid)
			return;

		m_grid[index] = n::sprite_bank::s_invalid;
		const auto& pair = m_tile_offsets[pos.y][pos.x];
		pair.first->delete_tile(pair.second);
		// TODO properly
		if (((sprite_batch*)pair.first)->is_empty())
		{
			m_batches.erase(std::find(m_batches.begin(), m_batches.end(), pair.first));
			MAGE_INFO("DELETE SB");
		}

		m_tile_offsets[pos.y].erase(pos.x);
		if (m_tile_offsets[pos.y].size() == 0)
			m_tile_offsets.erase(pos.y);
	}
}
