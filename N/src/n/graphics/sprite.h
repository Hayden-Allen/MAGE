#pragma once
#include "pch.h"
#include "wrap/texture.h"
#include "n/time.h"

namespace n
{
	class sprite final : public mage::dimensional<uint8_t>
	{
	public:
		sprite(const std::string& fp);
		N_DCM(sprite);
		~sprite()
		{
			delete m_texture;
		}


		const texture2d_array* const get_texture() const
		{
			return m_texture;
		}
	private:
		constexpr static size_t s_color_count = 16, s_pixels_per_side = 16, s_pixels_per_tile = 256;

		uint8_t m_frame, m_frame_count;
		uint16_t m_frame_time;
		time m_last_switch;
		texture2d_array* m_texture;
	};
}
