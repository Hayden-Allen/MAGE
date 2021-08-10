#include "pch.h"
#include "texture.h"
#include "mage/util/functions.h"

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
		if(data)
			arrprint(4 * w * h, (uint8_t*)data, "%u", ", ", 16);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}



	texture2d_array::texture2d_array(s_type w, s_type h, s_type f, void* data, const texture_options& options) :
		mage::gfx::texture2d_array(w, h, f, data),
		mage::dimensional<s_type>(w, h)
	{
		init(options);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, get_target_format(options.target_format), w, h, f, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
}
