#include "pch.h"
#include "sprite_atlas.h"
#include "sprite.h"
#include "mage/graphics/wrap/texture.h"

namespace mage
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		dimensional<coga::gfx::retained_texture2d::s_type>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(bank->add(this)),
		m_texture(new retained_texture2d(m_w, m_h, c::bytes_per_sprite_pixel* m_w* m_h, nullptr, s_texture_options))
	{}
	sprite_atlas::sprite_atlas(coga::input_file& in) :
		dimensional<coga::gfx::retained_texture2d::s_type>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(0),
		m_texture(new retained_texture2d(m_w, m_h, c::bytes_per_sprite_pixel* m_w * m_h, s_texture_options))
	{
		load(in);
	}



	void sprite_atlas::save(coga::output_file& out) const
	{
		COGA_ASSERT(false, "Cannot save a mage::sprite_atlas");
	}
	void sprite_atlas::load(coga::input_file& in)
	{
		// load index in bank
		m_handle = in.ushort();

		// load texture
		m_texture->load(in);
	}
}
