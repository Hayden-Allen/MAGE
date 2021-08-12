#include "pch.h"
#include "texture.h"
#include "mage/util/functions.h"

namespace mage::gfx
{
	texture2d* texture2d::create(s_type w, s_type h, const void* const data, const texture_options& options)
	{
		return new mage::gl::texture2d(w, h, data, MAGE_PUN(mage::gl::texture_options, options));
	}
	retained_texture2d* retained_texture2d::create(s_type w, s_type h, size_t count, const texture_options& options)
	{
		return new mage::gl::retained_texture2d(w, h, count, MAGE_PUN(mage::gl::texture_options, options));
	}
	retained_texture2d* retained_texture2d::create(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options)
	{
		return new mage::gl::retained_texture2d(w, h, count, data, MAGE_PUN(mage::gl::texture_options, options));
	}
	texture2d_array* texture2d_array::create(s_type w, s_type h, s_type f, const void* const data, const texture_options& options)
	{
		return new mage::gl::texture2d_array(w, h, f, data, MAGE_PUN(mage::gl::texture_options, options));
	}
}



namespace mage::gl
{
	texture2d::texture2d(s_type w, s_type h, const void* const data, const texture_options& options) :
		mage::gfx::texture2d(w, h),
		mage::dimensional<s_type>(w, h),
		m_options(options)
	{
		init(options);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		bind(0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}



	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options) :
		mage::gfx::retained_texture2d(w, h, count),
		mage::dimensional<s_type>(w, h),
		m_options(options)
	{
		init(options);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), nullptr);
	}
	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options) :
		mage::gfx::retained_texture2d(w, h, count, data),
		mage::dimensional<s_type>(w, h),
		m_options(options)
	{
		init(options);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void retained_texture2d::save(output_file& out) const
	{
		mage::gfx::retained_texture2d::save(out);
		serialize_texture_options(m_options, out);
	}
	void retained_texture2d::save(output_file& out, s_type x, s_type y, s_type w, s_type h) const
	{
		mage::gfx::retained_texture2d::save(out, x, y, w, h);
		serialize_texture_options(m_options, out);
	}
	void retained_texture2d::load(input_file& in)
	{
		mage::gfx::retained_texture2d::load(in);
		deserialize_texture_options(m_options, in);
		init(m_options);
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(m_options.target_format), m_w, m_h, 0, get_source_format(m_options.source_format), get_source_type(m_options.source_type), m_data);
	}
	void retained_texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		mage::gfx::retained_texture2d::update(x, y, w, h, data);
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
