#include "pch.h"
#include "map.h"
#include "chunk.h"

namespace orc
{
	map::map(sprite_atlas_bank* const atlases, sprite_bank* const sprites) :
		m_batches(new sprite_batch_bank()),
		m_atlases(atlases),
		m_sprites(sprites),
		m_chunk_count(0)
	{}
	map::~map()
	{
		delete m_batches;
		delete m_sprites;
		delete m_atlases;
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				delete pair.second;
	}



	void map::save(mage::output_file& out) const
	{
		m_batches->save(out);
		m_sprites->save(out);
		m_atlases->save(out);

		out.ulong(m_chunk_count);
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				pair.second->save(out);
	}
	void map::load(mage::input_file& in)
	{
		m_batches = new sprite_batch_bank(in);
		m_sprites = new sprite_bank(in);
		m_atlases = new sprite_atlas_bank(in);

		m_chunk_count = in.ulong();
		for (size_t i = 0; i < m_chunk_count; i++)
		{
			chunk* c = new chunk(*m_batches, in);

			const auto& pos = c->get_pos();
			if (!m_chunks.contains(pos.y))
				m_chunks.insert({ pos.y, {} });
			if (m_chunks[pos.y].contains(pos.x))
				MAGE_ASSERT(false, "Overlapping chunks at <{}, {}>", pos.x, pos.y);

			m_chunks[pos.y][pos.x] = c;
		}
	}
	void map::draw(const mage::timestep& t, const n::shader_program& shader)
	{
		/**
		 * TODO bad
		 */
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				pair.second->draw(t, m_sprites, m_atlases, shader);
	}
	void map::set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite)
	{
		if (!sprite)
			return;

		constexpr size_t s = n::c::tiles_per_chunk_side;
		const glm::uvec2 map_pos = pos / N_CAST(glm::uint, s), chunk_pos = pos % N_CAST(glm::uint, s);

		try_create_chunk(map_pos);

		if (can_set(pos, layer, sprite))
		{
			fill_grids(pos, { sprite->get_tile_w(), sprite->get_tile_h() }, layer, sprite_bank::s_placeholder);
			m_chunks[map_pos.y][map_pos.x]->set_tile_at(*m_batches, *m_sprites, chunk_pos, layer, sprite);
		}
	}
	void map::delete_tile_at(const glm::uvec2& pos, size_t layer)
	{
		constexpr size_t s = n::c::tiles_per_chunk_side;
		const glm::uvec2 map_pos = pos / N_CAST(glm::uint, s), chunk_pos = pos % N_CAST(glm::uint, s);

		// the given tile doesn't exist
		if (!has_chunk(map_pos) || m_chunks[map_pos.y][map_pos.x]->get_tile_at(chunk_pos, layer) == sprite_bank::s_invalid)
			return;

		const auto& [m, c] = find_root(pos, layer);
		chunk* const chunk = m_chunks[m.y][m.x];
		// get root tile
		chunk->delete_tile_at(*m_batches, *m_sprites, c, layer);
		// clear the area covered by root tile. This must be done after chunk::delete_tile_at because that method relies on the sprite handle in the grid
		const sprite* const existing = m_sprites->get(chunk->get_tile_at(c, layer));
		fill_grids(m * N_CAST(glm::uint, s) + c, { existing->get_tile_w(), existing->get_tile_h() }, layer, sprite_bank::s_invalid);
	}



	std::pair<glm::uvec2, glm::uvec2> map::find_root(const glm::uvec2& pos, size_t layer) const
	{
		// sweep rectangle between given pos and the furthest possible point that could be part of the same tile
		constexpr static size_t s = n::c::tiles_per_chunk_side;
		for (size_t i = pos.y; i >= glm::min(0ull, pos.y - s + 1); i--)
		{
			for (size_t j = pos.x; j >= glm::min(0ull, pos.x - s + 1); j--)
			{
				glm::uvec2 map_pos = { j / s, i / s }, chunk_pos = { j % s, i % s };
				if (has_chunk(map_pos) && sprite_bank::is_valid(m_chunks.at(map_pos.y).at(map_pos.x)->get_tile_at(chunk_pos, layer)))
					return { map_pos, chunk_pos };
			}
		}
		MAGE_ASSERT(false, "map::find_root fail");
		return { {0, 0}, {0, 0} };
	}
	void map::fill_grids(const glm::uvec2& pos, const glm::uvec2& dims, size_t layer, sprite_bank::handle h)
	{
		constexpr size_t s = n::c::tiles_per_chunk_side;
		for (size_t i = pos.y; i < N_CAST(size_t, pos.y) + dims.y; i++)
		{
			for (size_t j = pos.x; j < N_CAST(size_t, pos.x) + dims.x; j++)
			{
				const glm::uvec2 map_pos = { j / s, i / s };
				chunk* const chunk = try_create_chunk(map_pos);
				chunk->m_grid[chunk::get_index({ j % s, i % s }, layer)] = h;
			}
		}
	}
	bool map::can_set(const glm::uvec2& pos, size_t layer, const sprite* const sprite) const
	{
		constexpr size_t s = n::c::tiles_per_chunk_side;
		for (size_t i = pos.y; i < N_CAST(size_t, pos.y) + sprite->get_tile_h(); i++)
			for (size_t j = pos.x; j < N_CAST(size_t, pos.x) + sprite->get_tile_w(); j++)
			{
				const glm::uvec2 map_pos = { j / s, i / s };
				// this chunk doesn't exist yet. It will be created when the given sprite is added
				if (!has_chunk(map_pos))
					continue;
				const sprite_bank::handle existing = m_chunks.at(map_pos.y).at(map_pos.x)->get_tile_at({ j % s, i % s }, layer);
				// don't allow sprites inside other sprites or replacing a sprite with itself
				if (existing == sprite_bank::s_placeholder || existing == sprite->get_handle())
					return false;
			}
		return true;
		//// at this point the given chunk is guaranteed to exist because set_tile_at creates it
		//const sprite_bank::handle existing = m_chunks.at(map.y).at(map.x)->get_tile_at(chunk, layer);
		//return existing != sprite_bank::s_placeholder && existing != h;
	}
	chunk* const map::try_create_chunk(const glm::uvec2& pos)
	{
		if (!m_chunks.contains(pos.y))
			m_chunks.insert({ pos.y, {} });
		if (!m_chunks[pos.y].contains(pos.x))
		{
			chunk* const c = new chunk(N_CAST(glm::uint, n::c::tiles_per_chunk_side) * pos);
			m_chunks[pos.y].insert({ pos.x, c });
			m_chunk_count++;
			return c;
		}
		return m_chunks[pos.y][pos.x];
	}
}
