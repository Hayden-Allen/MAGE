#pragma once
#include "pch.h"
#include "sprite_atlas_bank.h"
#include "sprite_atlas_coords.h"
#include "mage/graphics/wrap/texture.h"
#include "coga/io/serializable.h"
#include "coga/util/dimensional.h"

namespace mage
{
	class sprite_atlas :
		public coga::dimensional<coga::gfx::retained_texture2d::s_type>,
		public coga::serializable
	{
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		sprite_atlas(coga::input_file& in);
		COGA_DCM(sprite_atlas);
		virtual ~sprite_atlas()
		{
			delete m_texture;
		}
	public:
		virtual void save(coga::output_file& out) const override;
		virtual void load(coga::input_file& in) override;
		void bind(uint32_t slot) const
		{
			m_texture->bind(slot);
		}
		sprite_atlas_bank::handle get_handle() const
		{
			return m_handle;
		}
	protected:
		constexpr static COGA_RAN::texture_options s_texture_options =
		{
			.min_filter = coga::gfx::texture_min_filter::nearest,
			.mag_filter = coga::gfx::texture_mag_filter::nearest,
			.wrap_s = coga::gfx::texture_wrap_s::clamp_border,
			.wrap_t = coga::gfx::texture_wrap_t::clamp_border
		};
	protected:
		// index of this atlas in its containing bank
		sprite_atlas_bank::handle m_handle;
		// hardware texture
		COGA_RAN::retained_texture2d* m_texture;
	protected:
		sprite_atlas(s_type w, s_type h) :
			coga::dimensional<coga::gfx::retained_texture2d::s_type>(w, h),
			m_handle(0),
			m_texture(nullptr)
		{}
	};
}
