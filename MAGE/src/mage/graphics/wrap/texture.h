#pragma once
#include "pch.h"

namespace mage
{
	typedef COGA_RAN::texture_options texture_options;
	typedef coga::gfx::texture_min_filter texture_min_filter;
	typedef coga::gfx::texture_mag_filter texture_mag_filter;
	typedef coga::gfx::texture_wrap_s texture_wrap_s;
	typedef coga::gfx::texture_wrap_t texture_wrap_t;
	typedef coga::gfx::texture_target_format texture_target_format;
	typedef coga::gfx::texture_source_format texture_source_format;
	typedef coga::gfx::texture_source_type texture_source_type;


	MAGE_WRAP
	(
		texture2d,
		texture2d,
		(s_type w, s_type h, const void* const data, const texture_options& options),
		(w, h, data, options)
	);


	MAGE_WRAP
	(
		retained_texture2d,
		retained_texture2d,
		(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options),
		(w, h, count, data, options),
		retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options) : COGA_RAN::retained_texture2d(w, h, count, options) {}
	);

	MAGE_WRAP
	(
		texture2d_array,
		texture2d_array,
		(s_type w, s_type h, s_type f, const void* const data, const texture_options& options),
		(w, h, f, data, options)
	);
}
