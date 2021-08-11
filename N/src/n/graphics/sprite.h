#pragma once
#include "pch.h"
#include "sprite_atlas.h"
#include "wrap/texture.h"
#include "n/time.h"

namespace n
{
	class sprite final : public mage::dimensional<uint8_t>
	{
	public:
		sprite(sprite_atlas* const atlas, const std::string& fp);
		N_DCM(sprite);


		template<typename T = uint8_t>
		T get_frame() const
		{
			return MAGE_CAST(T, m_frame);
		}
		const sprite_atlas_coords& get_coords() const
		{
			return m_coords;
		}
		void update(const time& t)
		{
			if (m_frame_count > 1 && t - m_last_switch >= m_frame_time)
			{
				m_frame = (m_frame + 1) % m_frame_count;
				m_last_switch = t;
			}
		}
	private:
		uint8_t m_frame, m_frame_count;
		uint16_t m_frame_time;
		time m_last_switch;
		sprite_atlas_coords m_coords;
	};
}
