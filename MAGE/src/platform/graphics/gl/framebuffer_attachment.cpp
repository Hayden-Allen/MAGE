#include "pch.h"
#include "framebuffer_attachment.h"

namespace mage::gfx
{
	framebuffer_color_attachment* framebuffer_color_attachment::create(s_type w, s_type h)
	{
		return new mage::gl::framebuffer_color_attachment(w, h);
	}
	framebuffer_depth_attachment* framebuffer_depth_attachment::create(s_type w, s_type h)
	{
		return new mage::gl::framebuffer_depth_attachment(w, h);
	}
}



namespace mage::gl
{
	framebuffer_color_attachment::framebuffer_color_attachment(s_type w, s_type h) :
		mage::gl::texture2d(w, h, nullptr, { .min_filter = mage::gfx::texture_min_filter::linear, .mag_filter = mage::gfx::texture_mag_filter::linear  }),
		mage::gfx::framebuffer_color_attachment(w, h),
		mage::dimensional<s_type>(w, h)
	{
		reset();
	}



	framebuffer_depth_attachment::framebuffer_depth_attachment(s_type w, s_type h) :
		mage::gl::texture2d(w, h, nullptr, {}),
		mage::gfx::framebuffer_depth_attachment(w, h),
		mage::dimensional<s_type>(w, h)
	{
		reset();
	}
}
