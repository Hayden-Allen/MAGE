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
	chunk::chunk(mage::input_file& in) :
		n::chunk_base<sprite_batch>({ 0, 0 }),
		m_tile_count(0),
		m_grid{ 0 }
	{
		load(in);
	}



	void chunk::save(mage::output_file& out) const
	{
		n::chunk_base<sprite_batch>::save(out);
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
		n::chunk_base<sprite_batch>::load(in);

		m_tile_count = in.ulong();
		in.read(m_grid, n::c::tiles_per_chunk);
	}
	void chunk::set_tile_at(const sprite_bank& sb, const glm::uvec2& pos, size_t layer, sprite* const sprite)
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
			added_to = new sprite_batch(m_coords);
			MAGE_ASSERT(added_to->can_contain(sprite), "Invalid tile");
			offset = added_to->add_tile(sb, t);
			m_batches.push_back(added_to);
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
		const size_t index = get_index(pos, layer);
		if (m_grid[index] == n::sprite_bank::s_invalid)
			return;

		// delete given tile from the batch that contains it
		m_grid[index] = n::sprite_bank::s_invalid;
		const auto& pair = m_tile_offsets[pos.y][pos.x];
		pair.first->delete_tile(pair.second);
		if (pair.first->is_empty())
			m_batches.erase(std::find(m_batches.begin(), m_batches.end(), pair.first));

		// remove given tile's record, because it no longer exists
		m_tile_offsets[pos.y].erase(pos.x);
		if (m_tile_offsets[pos.y].size() == 0)
			m_tile_offsets.erase(pos.y);
	}
}
