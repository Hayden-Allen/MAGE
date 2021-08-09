#include "pch.h"
#include "texture.h"

namespace mage::gfx
{
	texture2d* texture2d::create(s_type w, s_type h, void* data)
	{
		return new mage::gl::texture2d(w, h, data);
	}
	texture2d_array* texture2d_array::create(s_type w, s_type h, s_type f, void* data)
	{
		return new mage::gl::texture2d_array(w, h, f, data);
	}
}



namespace mage::gl
{

	template<GLenum T>
	texture<T>::texture(s_type w, s_type h, void* data) :
		mage::gfx::texture(w, h, data),
		mage::dimensional<s_type>(w, h)
	{
		glGenTextures(1, &m_id);
		bind(0);
		glTexParameteri(T, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(T, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(T, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(T, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	}
	template<GLenum T>
	texture<T>::~texture()
	{
		glDeleteTextures(1, &m_id);
	}



	texture2d::texture2d(s_type w, s_type h, void* data) :
		texture<GL_TEXTURE_2D>(w, h, data),
		mage::gfx::texture2d(w, h, data),
		mage::dimensional<s_type>(w, h)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}



	texture2d_array::texture2d_array(s_type w, s_type h, s_type f, void* data) :
		texture<GL_TEXTURE_2D_ARRAY>(w, h, data),
		mage::gfx::texture2d_array(w, h, f, data),
		mage::dimensional<s_type>(w, h)
	{
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, w, h, f, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}
