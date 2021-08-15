#include "pch.h"
#include "map.h"
#include "chunk.h"

namespace orc
{
	map::map(sprite_atlas_bank* const atlases, n::sprite_bank* const sprites, const std::vector<chunk*>& chunks) :
		m_atlases(atlases),
		m_sprites(sprites),
		m_chunks(chunks)
	{}
	map::~map()
	{
		delete m_atlases;
		delete m_sprites;
		for (chunk* c : m_chunks)
			delete c;
	}



	void map::save(mage::output_file& out) const
	{
		m_sprites->save(out);
		m_atlases->save(out);

		out.ulong(m_chunks.size());
		for (const chunk* const c : m_chunks)
			c->save(out);
	}
	void map::load(mage::input_file& in)
	{
		m_sprites = new n::sprite_bank(in);
		m_atlases = new sprite_atlas_bank(in);

		const size_t chunk_count = in.ulong();
		m_chunks.reserve(chunk_count);
		for (size_t i = 0; i < chunk_count; i++)
			m_chunks.push_back(new chunk(in));
	}
	void map::draw(const mage::timestep& t, const n::shader_program& shader)
	{
		/**
		 * TODO bad
		 */
		for (chunk* c : m_chunks)
			c->draw(t, m_sprites, m_atlases, shader);
	}
}
