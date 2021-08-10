#pragma once
#include "pch.h"
#include "mage/graphics/texture_options.h"

namespace mage::gl
{
	struct texture_options : public mage::gfx::texture_options
	{
		uint32_t min_filter = GL_NEAREST_MIPMAP_LINEAR, mag_filter = GL_NEAREST, wrap_s = GL_REPEAT, wrap_t = GL_REPEAT, target_format = GL_RGBA8, source_format = GL_RGBA, type = GL_UNSIGNED_BYTE;
	};
}
