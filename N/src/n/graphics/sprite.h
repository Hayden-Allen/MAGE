#pragma once
#include "pch.h"
#include "sprite_atlas.h"
#include "sprite_atlas_bank.h"
#include "wrap/texture.h"
#include "n/time.h"

namespace n
{
	class sprite final :
		public mage::dimensional<uint8_t>,
		public mage::serializable
	{
	private:
		struct frame_handle : public mage::serializable
		{
			sprite_atlas_bank::handle bank = 0;
			glm::vec2 offset = { 0.f, 0.f };


			frame_handle() {}
			frame_handle(sprite_atlas_bank::handle b, const glm::vec2& o) :
				bank(b),
				offset(o)
			{}
			frame_handle(const frame_handle& other) :
				bank(other.bank),
				offset(other.offset)
			{}


			void save(mage::output_file& out) const override
			{
				out.ubyte(bank);
				out.uint(N_PUN(uint32_t, offset.x)).uint(N_PUN(uint32_t, offset.y));
			}
			void load(mage::input_file& in) override
			{
				bank = in.ubyte();
				uint32_t x = in.uint(), y = in.uint();
				offset.x = N_PUN(float, x);
				offset.y = N_PUN(float, y);
			}
		};
	public:
		sprite(sprite_atlas_bank* const bank, const std::string& fp);
		N_DCM(sprite);


		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		template<typename T = uint8_t>
		T get_frame() const
		{
			return MAGE_CAST(T, m_frame);
		}
		const sprite_atlas_coords& get_base_coords() const
		{
			return m_base_coords;
		}
		const frame_handle& get_current_frame() const
		{
			return m_frame_data[m_frame];
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
		sprite_atlas_coords m_base_coords;
		std::vector<frame_handle> m_frame_data;


		bool add_to_atlas(sprite_atlas* const atlas, const uint8_t* const color_data, size_t i)
		{
			// attempt to add
			const auto& c = atlas->insert(m_w, m_h, color_data + i * m_w * m_h * c::bytes_per_pixel);
			// given atlas doesn't have room for this sprite
			if (c.is_invalid())
				return false;

			// first frame
			if (i == 0)
				m_base_coords = c;
			// for all frames, store delta between base coords and returned coords
			m_frame_data.push_back(frame_handle(atlas->get_handle(), c - m_base_coords));
			return true;
		}
	};
}
