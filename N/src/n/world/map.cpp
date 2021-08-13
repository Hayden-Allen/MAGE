#include "pch.h"
#include "map.h"
#include "chunk.h"

namespace n
{
	map::map(sprite_atlas_bank* const atlases, sprite_bank* const sprites, const std::vector<chunk*>& chunks) :
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



	void map::draw(const timestep& t, const shader_program& shader)
	{
		shader.bind();
		for (chunk* c : m_chunks)
			c->draw(t, m_sprites, m_atlases, shader);
	}
}
