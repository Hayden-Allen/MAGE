#include "pch.h"
#include "sprite_atlas.h"
#include "sprite_atlas_bank.h"

namespace orc
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		n::sprite_atlas(n::c::sprite_atlas_size, n::c::sprite_atlas_size),
		rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>(n::c::sprite_atlas_size, n::c::sprite_atlas_size)
	{
		m_handle = bank->add(this);
		m_texture = mage::gfx::retained_texture2d::create(n::sprite_atlas::m_w, n::sprite_atlas::m_h, n::c::bytes_per_sprite_pixel * n::sprite_atlas::m_w * n::sprite_atlas::m_h, nullptr, s_texture_options);
	}
	sprite_atlas::sprite_atlas(mage::input_file& in) :
		n::sprite_atlas(in),
		rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>(in)
	{}


	void sprite_atlas::save(mage::output_file& out) const
	{
		out.ushort(m_handle);
		m_texture->save(out, 0, 0, m_x_max, m_y_max);
		mage::rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>::save(out);
	}
	void sprite_atlas::load(mage::input_file& in)
	{
		 n::sprite_atlas::load(in);
		 mage::rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>::load(in);
	}



	n::sprite_atlas_coords sprite_atlas::insert(const point& dims, const rect& spot, const uint8_t* const data)
	{
		const uint32_t x_start = spot.min.x;
		const uint32_t y_start = spot.min.y;
		m_texture->update(x_start, y_start, dims.x, dims.y, data);

		return mage::rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>::insert(dims, spot, data);
	}
}
