#pragma once
#include "pch.h"
#include "sprite_atlas_bank.h"
#include "sprite_atlas_coords.h"
#include "mage/io/serializable.h"
#include "mage/util/dimensional.h"

namespace mage::game
{
	class sprite_atlas :
		public dimensional<gfx::retained_texture2d::s_type>,
		public serializable
	{
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		sprite_atlas(input_file& in);
		MAGE_DCM(sprite_atlas);
		~sprite_atlas()
		{
			delete m_texture;
		}


		virtual void save(output_file& out) const override;
		virtual void load(input_file& in) override;
		void bind(uint32_t slot) const
		{
			m_texture->bind(slot);
		}
		sprite_atlas_bank::handle get_handle() const
		{
			return m_handle;
		}
	protected:
		constexpr static MAGE_RAN::texture_options s_texture_options =
		{
			.min_filter = gfx::texture_min_filter::nearest,
			.mag_filter = gfx::texture_mag_filter::nearest,
			.wrap_s = gfx::texture_wrap_s::clamp_border,
			.wrap_t = gfx::texture_wrap_t::clamp_border
		};


		// index of this atlas in its containing bank
		sprite_atlas_bank::handle m_handle;
		// hardware texture
		gfx::retained_texture2d* m_texture;
	};
}
