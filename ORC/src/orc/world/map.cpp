#include "pch.h"
#include "map.h"
#include "chunk.h"

namespace orc
{
	map::map() :
		mage::map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>(new sprite_atlas_bank(), new sprite_bank()),
		m_batches(new sprite_batch_bank())
	{}
	map::map(sprite_atlas_bank* const atlases, sprite_bank* const sprites) :
		mage::map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>(atlases, sprites),
		m_batches(new sprite_batch_bank())
	{}
	map::~map()
	{
		delete m_batches;
	}



	// TODO must line up with mage::map::load
	void map::build(coga::output_file& out) const
	{
		m_sprites->build(out);
		m_atlases->build(out);

		out.ulong(m_chunk_count);
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				pair.second->build(out);
	}
	void map::save(coga::output_file& out) const
	{
		m_batches->save(out);
		m_sprites->save(out);
		m_atlases->save(out);

		out.ulong(m_chunk_count);
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				pair.second->save(out);
	}
	void map::load(coga::input_file& in)
	{
		m_batches = new sprite_batch_bank(in);
		mage::map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>::load(in);


		for (size_t i = 0; i < m_chunk_count; i++)
			add_chunk(new chunk(*m_batches, in));
	}
	void map::set_tile_at(const glm::uvec2& pos, size_t layer, const sprite* const sprite)
	{
		if (!sprite)
			return;

		constexpr size_t s = mage::c::tiles_per_chunk_side;
		const glm::uvec2 map_pos = pos / COGA_CAST(glm::uint, s), chunk_pos = pos % COGA_CAST(glm::uint, s);

		try_create_chunk(map_pos);

		if (can_set(pos, layer, sprite))
		{
			fill_grids(pos, { sprite->get_tile_w(), sprite->get_tile_h() }, layer, sprite_bank::s_placeholder);
			m_chunks[map_pos.y][map_pos.x]->set_tile_at(*m_batches, *m_sprites, chunk_pos, layer, sprite);
		}
	}
	void map::delete_tile_at(const glm::uvec2& pos, size_t layer)
	{
		constexpr size_t s = mage::c::tiles_per_chunk_side;
		const glm::uvec2 map_pos = pos / COGA_CAST(glm::uint, s), chunk_pos = pos % COGA_CAST(glm::uint, s);

		// the given tile doesn't exist
		if (!has_chunk(map_pos) || m_chunks[map_pos.y][map_pos.x]->get_tile_at(chunk_pos, layer) == sprite_bank::s_invalid)
			return;

		const auto& [m, c] = find_root(pos, layer);
		chunk* const chunk = m_chunks[m.y][m.x];
		// get root tile
		chunk->delete_tile_at(*m_batches, *m_sprites, c, layer);
		// clear the area covered by root tile. This must be done after chunk::delete_tile_at because that method relies on the sprite handle in the grid
		const sprite* const existing = m_sprites->get(chunk->get_tile_at(c, layer));
		fill_grids(m * COGA_CAST(glm::uint, s) + c, { existing->get_tile_w(), existing->get_tile_h() }, layer, sprite_bank::s_invalid);

		if (chunk->is_empty())
		{
			m_chunks[m.y].erase(m.x);
			if (m_chunks[m.y].empty())
				m_chunks.erase(m.y);
			delete chunk;
		}
	}



	std::pair<glm::uvec2, glm::uvec2> map::find_root(const glm::uvec2& pos, size_t layer) const
	{
		// sweep rectangle between given pos and the furthest possible point that could be part of the same tile
		constexpr size_t s = mage::c::tiles_per_chunk_side;

		// these need to be signed because minx/miny can be 0, so indices need to be able to go negative for the loop to terminate
		const int maxx = COGA_CAST(int, pos.x), minx = COGA_CAST(int, std::min(0ull, pos.x - s + 1));
		const int maxy = COGA_CAST(int, pos.y), miny = COGA_CAST(int, std::min(0ull, pos.y - s + 1));
		for (int i = maxy; i >= miny; i--)
		{
			for (int j = maxx; j >= minx; j--)
			{
				glm::uvec2 map_pos = { j / s, i / s }, chunk_pos = { j % s, i % s };
				if (has_chunk(map_pos) && sprite_bank::is_valid(m_chunks.at(map_pos.y).at(map_pos.x)->get_tile_at(chunk_pos, layer)))
					return { map_pos, chunk_pos };
			}
		}
		COGA_ASSERT(false, "map::find_root fail");
		return { { 0, 0 }, { 0, 0 } };
	}
	void map::fill_grids(const glm::uvec2& pos, const glm::uvec2& dims, size_t layer, sprite_bank::handle h)
	{
		constexpr size_t s = mage::c::tiles_per_chunk_side;
		for (size_t i = pos.y; i < COGA_CAST(size_t, pos.y) + dims.y; i++)
		{
			for (size_t j = pos.x; j < COGA_CAST(size_t, pos.x) + dims.x; j++)
			{
				const glm::uvec2 map_pos = { j / s, i / s };
				chunk* const chunk = try_create_chunk(map_pos);
				chunk->m_grid[chunk::get_index({ j % s, i % s }, layer)] = h;
			}
		}
	}
	bool map::can_set(const glm::uvec2& pos, size_t layer, const sprite* const sprite) const
	{
		constexpr size_t s = mage::c::tiles_per_chunk_side;
		for (size_t i = pos.y; i < COGA_CAST(size_t, pos.y) + sprite->get_tile_h(); i++)
			for (size_t j = pos.x; j < COGA_CAST(size_t, pos.x) + sprite->get_tile_w(); j++)
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
			chunk* const c = new chunk(COGA_CAST(glm::uint, mage::c::tiles_per_chunk_side) * pos);
			m_chunks[pos.y].insert({ pos.x, c });
			m_chunk_count++;
			return c;
		}
		return m_chunks[pos.y][pos.x];
	}
}
