#pragma once
#include "pch.h"
#include "sprite_atlas_bank.h"
#include "sprite_atlas_coords.h"
#include "n/graphics/wrap/texture.h"
#include "mage/io/serializable.h"
#include "mage/util/dimensional.h"

namespace n
{
	class sprite_atlas :
		public mage::dimensional<mage::gfx::retained_texture2d::s_type>,
		public mage::serializable
	{
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		sprite_atlas(mage::input_file& in);
		MAGE_DCM(sprite_atlas);
		virtual ~sprite_atlas()
		{
			delete m_texture;
		}
	public:
		virtual void save(mage::output_file& out) const override;
		virtual void load(mage::input_file& in) override;
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
			.min_filter = mage::gfx::texture_min_filter::nearest,
			.mag_filter = mage::gfx::texture_mag_filter::nearest,
			.wrap_s = mage::gfx::texture_wrap_s::clamp_border,
			.wrap_t = mage::gfx::texture_wrap_t::clamp_border
		};
	protected:
		// index of this atlas in its containing bank
		sprite_atlas_bank::handle m_handle;
		// hardware texture
		n::retained_texture2d* m_texture;
	protected:
		sprite_atlas(s_type w, s_type h) :
			mage::dimensional<mage::gfx::retained_texture2d::s_type>(w, h),
			m_handle(0),
			m_texture(nullptr)
		{}
	};
}
