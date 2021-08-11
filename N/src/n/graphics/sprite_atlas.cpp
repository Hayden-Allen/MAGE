#include "pch.h"
#include "sprite_atlas.h"
#include "sprite.h"

namespace n
{
	sprite_atlas::sprite_atlas() :
		mage::dimensional3<uint32_t>(c::sprite_atlas_size, c::sprite_atlas_size, c::max_frame_count),
		m_texture(nullptr)
	{
		m_texture = new n::texture2d_array(m_w, m_h, m_d, nullptr,
			{
				.min_filter = texture_min_filter::nearest,
				.mag_filter = texture_mag_filter::nearest,
				.wrap_s = texture_wrap_s::clamp_border,
				.wrap_t = texture_wrap_t::clamp_border
			}
		);
	}



	sprite_atlas_coords sprite_atlas::insert(s_type w, s_type h, s_type frames, const uint8_t* const data)
	{
		m_texture->update(0, 0, 0, w, h, frames, data);
		return { { 0.f, w / get_w<float>() }, {0.f, h / get_h<float>() } };
	}
}
