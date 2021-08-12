#pragma once
#include "pch.h"

namespace n
{
	typedef MAGE_RAN::texture_options texture_options;
	typedef mage::gfx::texture_min_filter texture_min_filter;
	typedef mage::gfx::texture_mag_filter texture_mag_filter;
	typedef mage::gfx::texture_wrap_s texture_wrap_s;
	typedef mage::gfx::texture_wrap_t texture_wrap_t;
	typedef mage::gfx::texture_target_format texture_target_format;
	typedef mage::gfx::texture_source_format texture_source_format;
	typedef mage::gfx::texture_source_type texture_source_type;


	N_WRAP_VIRTUAL
	(
		texture2d,
		texture2d,
		(s_type w, s_type h, const void* const data, const texture_options& options) : mage::dimensional<s_type>(w, h),
		(w, h, data, options)
	);


	N_WRAP_VIRTUAL
	(
		retained_texture2d,
		retained_texture2d,
		(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options) : mage::dimensional<s_type>(w, h),
		(w, h, count, data, options),
		retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options) : mage::dimensional<s_type>(w, h), MAGE_RAN::retained_texture2d(w, h, count, options) {}
	);

	N_WRAP_VIRTUAL
	(
		texture2d_array,
		texture2d_array,
		(s_type w, s_type h, s_type f, const void* const data, const texture_options& options) : mage::dimensional<s_type>(w, h),
		(w, h, f, data, options)
	);
}
