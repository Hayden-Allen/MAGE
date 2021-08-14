#include "pch.h"
#include "sprite_atlas.h"

using namespace mage::game;

namespace orc
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		mage::game::sprite_atlas(bank),
		rect_packer<uint32_t, sprite_atlas_coords, uint8_t>(c::sprite_atlas_size, c::sprite_atlas_size)
	{

	}
	sprite_atlas::sprite_atlas(input_file& in) :
		mage::game::sprite_atlas(in),
		rect_packer<uint32_t, sprite_atlas_coords, uint8_t>(in)
	{}


	void sprite_atlas::save(output_file& out) const
	{
		out.ushort(m_handle);
		m_texture->save(out, 0, 0, m_x_max, m_y_max);
		rect_packer<uint32_t, sprite_atlas_coords, uint8_t>::save(out);
	}
	void sprite_atlas::load(input_file& in)
	{
		mage::game::sprite_atlas::load(in);
		rect_packer<uint32_t, sprite_atlas_coords, uint8_t>::load(in);
	}



	sprite_atlas_coords sprite_atlas::insert(const point& dims, const rect& spot, const uint8_t* const data)
	{
		const uint32_t x_start = spot.min.x;
		const uint32_t y_start = spot.min.y;
		m_texture->update(x_start, y_start, dims.x, dims.y, data);

		return rect_packer<uint32_t, sprite_atlas_coords, uint8_t>::insert(dims, spot, data);
	}
}
