#include "pch.h"
#include "framebuffer_attachment.h"

namespace mage::gl
{
	framebuffer_color_attachment::framebuffer_color_attachment(s_type w, s_type h) :
	mage::gl::framebuffer_attachment<mage::gfx::framebuffer_color_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr, { .min_filter = mage::gfx::texture_min_filter::linear, .mag_filter = mage::gfx::texture_mag_filter::linear })
	{
		reset();
	}



	framebuffer_depth_attachment::framebuffer_depth_attachment(s_type w, s_type h) :
		mage::gl::framebuffer_attachment<mage::gfx::framebuffer_depth_attachment<mage::gl::texture2d, const void* const, const texture_options&>, const void* const, const texture_options&>(w, h, nullptr, { .min_filter = mage::gfx::texture_min_filter::linear, .mag_filter = mage::gfx::texture_mag_filter::linear }
		)
	{
		reset();
	}
}
