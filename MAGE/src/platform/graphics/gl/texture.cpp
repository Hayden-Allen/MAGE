#include "pch.h"
#include "texture.h"
#include "mage/util/functions.h"

namespace mage::gfx
{
	texture2d* texture2d::create(s_type w, s_type h, const void* const data, const texture_options& options)
	{
		return new mage::gl::texture2d(w, h, data, MAGE_PUN(mage::gl::texture_options, options));
	}
	texture2d_array* texture2d_array::create(s_type w, s_type h, s_type f, const void* const data, const texture_options& options)
	{
		return new mage::gl::texture2d_array(w, h, f, data, MAGE_PUN(mage::gl::texture_options, options));
	}
}



namespace mage::gl
{
	texture2d::texture2d(s_type w, s_type h, const void* const data, const texture_options& options) :
		mage::gfx::texture2d(w, h, data),
		mage::dimensional<s_type>(w, h),
		m_options(options)
	{
		init(options);
		if(data)
			arrprint(4 * w * h, (uint8_t*)data, "%u", ", ", 16);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		bind(0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}


	texture2d_array::texture2d_array(s_type w, s_type h, s_type f, const void* const data, const texture_options& options) :
		mage::gfx::texture2d_array(w, h, f, data),
		mage::dimensional<s_type>(w, h),
		m_options(options)
	{
		init(options);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, get_target_format(options.target_format), w, h, f, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d_array::update(s_type x, s_type y, s_type z, s_type w, s_type h, s_type d, const void* const data)
	{
		bind(0);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, x, y, z, w, h, d, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}
}
