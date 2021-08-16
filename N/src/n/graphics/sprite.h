#pragma once
#include "pch.h"
#include "sprite_atlas.h"
#include "sprite_atlas_bank.h"
#include "sprite_bank.h"
#include "mage/timestep.h"

namespace n
{
	class sprite :
		public mage::dimensional<uint8_t>,
		public mage::serializable
	{
	protected:
		/**
		 * Structure to hold all necessary info for a given frame. Index of its containing sprite_atlas and the offset between its texture coordinates and the first frame's texture coordinates
		 */
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
				out.ushort(bank);
				out.uint(MAGE_PUN(uint32_t, offset.x)).uint(MAGE_PUN(uint32_t, offset.y));
			}
			void load(mage::input_file& in) override
			{
				bank = in.ushort();
				uint32_t x = in.uint(), y = in.uint();
				offset.x = MAGE_PUN(float, x);
				offset.y = MAGE_PUN(float, y);
			}
		};
	public:
		sprite(mage::input_file& in);
		MAGE_DCM(sprite);
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		void update(const mage::timestep& t);
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
		const sprite_bank::handle get_handle() const
		{
			return m_handle;
		}
	protected:
		sprite_bank::handle m_handle;
		// current frame, number of frames
		uint8_t m_frame, m_frame_count;
		// time (ms) that each frame should display for
		uint16_t m_frame_time;
		// time at which m_frame was last updated
		mage::timestep m_last_switch;
		// texture coords of first frame
		sprite_atlas_coords m_base_coords;
		// data for all frames
		std::vector<frame_handle> m_frame_data;
	protected:
		sprite(sprite_bank* const sb) :
			mage::dimensional<uint8_t>(0, 0),
			m_handle(sb->add(this)),
			m_frame(0),
			m_frame_count(0),
			m_frame_time(0),
			m_base_coords({ 0.f, 1.f }, { 0.f, 1.f })
		{}
	};
}

