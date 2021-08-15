#include "pch.h"
#include "framebuffer_attachment.h"

namespace mage::gl
{
	framebuffer_color_attachment::framebuffer_color_attachment(s_type w, s_type h) :
	mage::gl::framebuffer_attachment<mage::gfx::framebuffer_color_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr,
		{
			.min_filter = mage::gfx::texture_min_filter::linear,
			.mag_filter = mage::gfx::texture_mag_filter::linear
		}
	),
		dimensional<s_type>(w, h)
	{
		reset();
	}



	framebuffer_depth_attachment::framebuffer_depth_attachment(s_type w, s_type h) :
		mage::gl::framebuffer_attachment<mage::gfx::framebuffer_depth_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr,
			{
				.min_filter = mage::gfx::texture_min_filter::linear,
				.mag_filter = mage::gfx::texture_mag_filter::linear
			}
		),
		dimensional<s_type>(w, h)
	{
		reset();
	}


	/*mage::gl::texture2d(w, h, nullptr, { .min_filter = mage::gfx::texture_min_filter::linear, .mag_filter = mage::gfx::texture_mag_filter::linear  }),
	mage::gfx::framebuffer_color_attachment(w, h),
	mage::dimensional<s_type>(w, h)*/


	/*mage::gl::texture2d(w, h, nullptr, {}),
	mage::gfx::framebuffer_depth_attachment(w, h),
	mage::dimensional<s_type>(w, h)*/
}
