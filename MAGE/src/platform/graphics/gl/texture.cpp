#include "pch.h"
#include "texture.h"
#include "mage/util/functions.h"

namespace mage::gl
{
	template<typename T, GLenum TARGET, typename ... ARGS>
	void texture<T, TARGET, ARGS...>::init(const texture_options& options)
	{
		glGenTextures(1, &this->m_id);
		bind(0);
		glTexParameteri(TARGET, GL_TEXTURE_MIN_FILTER, get_min_filter(options.min_filter));
		glTexParameteri(TARGET, GL_TEXTURE_MAG_FILTER, get_mag_filter(options.mag_filter));
		glTexParameteri(TARGET, GL_TEXTURE_WRAP_S, get_wrap_s(options.wrap_s));
		glTexParameteri(TARGET, GL_TEXTURE_WRAP_T, get_wrap_t(options.wrap_t));
	}



	texture2d::texture2d(s_type w, s_type h, const void* const data, const texture_options& options) :
		mage::gl::texture<mage::gfx::texture2d, GL_TEXTURE_2D>(options, w, h)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
	}
	void texture2d::update(s_type x, s_type y, s_type w, s_type h, const void* const data)
	{
		bind(0);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, get_source_format(m_options.source_format), get_source_type(m_options.source_type), data);
	}



	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const texture_options& options) :
		mage::gl::texture<mage::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>(options, w, h, count, nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), nullptr);
	}
	retained_texture2d::retained_texture2d(s_type w, s_type h, size_t count, const uint32_t* const data, const texture_options& options) :
		mage::gl::texture<mage::gfx::retained_texture2d, GL_TEXTURE_2D, size_t, const uint32_t* const>(options, w, h, count, data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, get_target_format(options.target_format), w, h, 0, get_source_format(options.source_format), get_source_type(options.source_type), data);
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
		mage::gl::texture<mage::gfx::texture2d_array, GL_TEXTURE_2D_ARRAY, mage::gfx::texture2d_array::s_type>(options, w, h, f)
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
