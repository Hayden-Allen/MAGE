#pragma once
#include "pch.h"
#include "mage/graphics/texture_options.h"

namespace mage::gl
{
	static GLenum min_filter[] =
	{
		GL_NONE, GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
	};
	static GLenum get_min_filter(mage::gfx::texture_min_filter f)
	{
		MAGE_CORE_ASSERT(f != mage::gfx::texture_min_filter::none, "Invalid OpenGL texture min filter");
		return min_filter[MAGE_CAST(size_t, f)];
	}
	static GLenum mag_filter[] =
	{
		GL_NONE, GL_NEAREST, GL_LINEAR
	};
	static GLenum get_mag_filter(mage::gfx::texture_mag_filter f)
	{
		MAGE_CORE_ASSERT(f != mage::gfx::texture_mag_filter::none, "Invalid OpenGL texture mag filter");
		return mag_filter[MAGE_CAST(size_t, f)];
	}
	static GLenum wrap_s[] =
	{
		GL_NONE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, GL_MIRROR_CLAMP_TO_EDGE
	};
	static GLenum get_wrap_s(mage::gfx::texture_wrap_s w)
	{
		MAGE_CORE_ASSERT(w != mage::gfx::texture_wrap_s::none, "Invalid OpenGL texture wrap s mode");
		return wrap_s[MAGE_CAST(size_t, w)];
	}
	static GLenum wrap_t[] =
	{
		GL_NONE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, GL_MIRROR_CLAMP_TO_EDGE
	};
	static GLenum get_wrap_t(mage::gfx::texture_wrap_t w)
	{
		MAGE_CORE_ASSERT(w != mage::gfx::texture_wrap_t::none, "Invalid OpenGL texture wrap t mode");
		return wrap_t[MAGE_CAST(size_t, w)];
	}
	static GLenum target_format[] =
	{
		GL_NONE, GL_RGBA8
	};
	static GLenum get_target_format(mage::gfx::texture_target_format f)
	{
		MAGE_CORE_ASSERT(f != mage::gfx::texture_target_format::none, "Invalid OpenGL texture target format");
		return target_format[MAGE_CAST(size_t, f)];
	}
	static GLenum source_format[] =
	{
		GL_NONE, GL_RGBA
	};
	static GLenum get_source_format(mage::gfx::texture_source_format f)
	{
		MAGE_CORE_ASSERT(f != mage::gfx::texture_source_format::none, "Invalid OpenGL texture source format");
		return source_format[MAGE_CAST(size_t, f)];
	}
	static GLenum source_type[] =
	{
		GL_NONE, GL_UNSIGNED_BYTE
	};
	static GLenum get_source_type(mage::gfx::texture_source_type t)
	{
		MAGE_CORE_ASSERT(t != mage::gfx::texture_source_type::none, "Invalid OpenGL texture source type");
		return source_type[MAGE_CAST(size_t, t)];
	}



	struct texture_options : public mage::gfx::texture_options
	{
		mage::gfx::texture_min_filter min_filter = mage::gfx::texture_min_filter::nearest_linear;
		mage::gfx::texture_mag_filter mag_filter = mage::gfx::texture_mag_filter::linear;
		mage::gfx::texture_wrap_s wrap_s = mage::gfx::texture_wrap_s::repeat;
		mage::gfx::texture_wrap_t wrap_t = mage::gfx::texture_wrap_t::repeat;
		mage::gfx::texture_target_format target_format = mage::gfx::texture_target_format::rgba8;
		mage::gfx::texture_source_format source_format = mage::gfx::texture_source_format::rgba;
		mage::gfx::texture_source_type source_type = mage::gfx::texture_source_type::byte;
	};
}
