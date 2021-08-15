#include "pch.h"
#include "sprite_batch.h"

namespace n
{
	sprite_batch_base::~sprite_batch_base()
	{
		delete m_indices;
		delete m_vertices;
		delete m_vertex_array;
	}



	void sprite_batch_base::add_sprite(sprite_bank::handle sprite)
	{
		m_sprites.push_back(sprite);
		m_offsets.push_back({ 0.f, 0.f });
		m_texture_indices.push_back(0);
	}



	void sprite_batch_base::save(mage::output_file& out) const
	{
		const size_t atlas_count = m_atlases.size();
		out.ulong(atlas_count);
		for (const auto& pair : m_atlases)
			out.ushort(pair.first).ulong(pair.second);

		out.ulong(m_sprites.size());
		for (const auto& s : m_sprites)
			out.ushort(s);
	}
	void sprite_batch_base::load(mage::input_file& in)
	{
		const size_t atlas_count = in.ulong();
		m_atlases.reserve(atlas_count);
		for (size_t i = 0; i < atlas_count; i++)
			m_atlases.insert({ in.ushort(), in.ulong() });

		const size_t sprite_count = in.ulong();
		m_sprites.reserve(sprite_count);
		for (size_t i = 0; i < sprite_count; i++)
			add_sprite(in.ushort());
	}
}
