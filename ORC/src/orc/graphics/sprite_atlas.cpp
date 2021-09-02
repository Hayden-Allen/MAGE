#include "pch.h"
#include "sprite_atlas.h"
#include "sprite_atlas_bank.h"

namespace orc
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		mage::sprite_atlas(mage::c::sprite_atlas_size, mage::c::sprite_atlas_size),
		rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>(mage::c::sprite_atlas_size, mage::c::sprite_atlas_size)
	{
		m_handle = bank->add(this);
		m_texture = new mage::retained_texture2d(mage::sprite_atlas::m_w, mage::sprite_atlas::m_h, mage::c::bytes_per_sprite_pixel * mage::sprite_atlas::m_w * mage::sprite_atlas::m_h, nullptr, s_texture_options);
	}
	sprite_atlas::sprite_atlas(coga::input_file& in) :
		mage::sprite_atlas(in),
		rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>(in)
	{}



	void sprite_atlas::save(coga::output_file& out) const
	{
		out.ushort(m_handle);
		m_texture->save(out, 0, 0, m_x_max, m_y_max);
		coga::rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>::save(out);
	}
	void sprite_atlas::load(coga::input_file& in)
	{
		 mage::sprite_atlas::load(in);
		 coga::rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>::load(in);
	}



	mage::sprite_atlas_coords sprite_atlas::insert(const point& dims, const rect& spot, const uint8_t* const data)
	{
		const uint32_t x_start = spot.min.x;
		const uint32_t y_start = spot.min.y;
		m_texture->update(x_start, y_start, dims.x, dims.y, data);

		return coga::rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>::insert(dims, spot, data);
	}
}
