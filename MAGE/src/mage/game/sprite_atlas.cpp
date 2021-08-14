#include "pch.h"
#include "sprite_atlas.h"
#include "sprite.h"

namespace mage::game
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		dimensional<gfx::retained_texture2d::s_type>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(bank->add(this)),
		m_texture(nullptr)
	{
		m_texture = gfx::retained_texture2d::create(m_w, m_h, c::bytes_per_sprite_pixel * m_w * m_h, nullptr, s_texture_options);
	}
	sprite_atlas::sprite_atlas(mage::input_file& in) :
		dimensional<gfx::retained_texture2d::s_type>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(0),
		m_texture(gfx::retained_texture2d::create(m_w, m_h, c::bytes_per_sprite_pixel* m_w * m_h, s_texture_options))
	{
		load(in);
	}



	void sprite_atlas::save(mage::output_file& out) const
	{
		// save index in bank
		out.ushort(m_handle);

		// save texture
		m_texture->save(out);
	}
	void sprite_atlas::load(mage::input_file& in)
	{
		// load index in bank
		m_handle = in.ushort();

		// load texture
		m_texture->load(in);
	}
}
