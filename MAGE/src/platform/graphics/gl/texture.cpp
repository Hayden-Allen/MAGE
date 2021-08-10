#include "pch.h"
#include "texture.h"

namespace mage::gfx
{
	texture2d* texture2d::create(s_type w, s_type h, void* data, const texture_options& options)
	{
		return new mage::gl::texture2d(w, h, data, MAGE_PUN(mage::gl::texture_options, options));
	}
	texture2d_array* texture2d_array::create(s_type w, s_type h, s_type f, void* data, const texture_options& options)
	{
		return new mage::gl::texture2d_array(w, h, f, data, MAGE_PUN(mage::gl::texture_options, options));
	}
}



namespace mage::gl
{
	texture2d::texture2d(s_type w, s_type h, void* data, const texture_options& options) :
		mage::gfx::texture2d(w, h, data),
		mage::dimensional<s_type>(w, h)
	{
		init(options);
		glTexImage2D(GL_TEXTURE_2D, 0, options.target_format, w, h, 0, options.source_format, options.type, data);
	}



	texture2d_array::texture2d_array(s_type w, s_type h, s_type f, void* data, const texture_options& options) :
		mage::gfx::texture2d_array(w, h, f, data),
		mage::dimensional<s_type>(w, h)
	{
		init(options);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, options.target_format, w, h, f, 0, options.source_format, options.type, data);
	}
}
