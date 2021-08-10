#pragma once
#include "pch.h"

namespace n
{
	typedef MAGE_RAN::texture_options texture_options;


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
