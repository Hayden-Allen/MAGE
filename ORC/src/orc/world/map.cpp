#include "pch.h"
#include "map.h"
#include "chunk.h"

namespace orc
{
	map::map(sprite_atlas_bank* const atlases, n::sprite_bank* const sprites, const grid& chunks) :
		m_atlases(atlases),
		m_sprites(sprites),
		m_chunks(chunks)
	{}
	map::~map()
	{
		delete m_atlases;
		delete m_sprites;
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				delete pair.second;
	}



	void map::save(mage::output_file& out) const
	{
		m_sprites->save(out);
		m_atlases->save(out);

		out.ulong(m_chunks.size());
		for (auto& row : m_chunks)
			for (auto& pair : row.second)
				pair.second->save(out);
	}
	void map::load(mage::input_file& in)
	{
		m_sprites = new n::sprite_bank(in);
		m_atlases = new sprite_atlas_bank(in);

		const size_t chunk_count = in.ulong();
		for (size_t i = 0; i < chunk_count; i++)
		{
			chunk* c = new chunk(in);

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
		const glm::uvec2 chunk = pos / N_CAST(glm::uint, n::c::tiles_per_chunk_side), chunk_pos = pos % N_CAST(glm::uint, n::c::tiles_per_chunk_side);

		if (!m_chunks.contains(chunk.y) || !m_chunks[chunk.y].contains(chunk.x))
			MAGE_ASSERT(false, "Invalid chunk coords <{}, {}>", chunk.x, chunk.y);

		m_chunks[chunk.y][chunk.x]->set_tile_at(chunk_pos, layer, sprite);
	}
}
