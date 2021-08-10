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
		(s_type w, s_type h, void* data, const texture_options& options) : mage::dimensional<s_type>(w, h),
		(w, h, data, options)
	);



	N_WRAP_VIRTUAL
	(
		texture2d_array,
		texture2d_array,
		(s_type w, s_type h, s_type f, void* data, const texture_options& options) : mage::dimensional<s_type>(w, h),
		(w, h, f, data, options)
	);
}
