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
	/*template<GLenum INTERNAL, GLenum FORMAT, GLenum TYPE>
	framebuffer_attachment<INTERNAL, FORMAT, TYPE>::framebuffer_attachment(s_type w, s_type h) :
		mage::gfx::framebuffer_attachment(w, h),
		texture2d(w, h, nullptr, {}),
		dimensional<uint32_t>(w, h)
	{
		glGenTextures(1, &m_id);
	}
	template<GLenum INTERNAL, GLenum FORMAT, GLenum TYPE>
	framebuffer_attachment<INTERNAL, FORMAT, TYPE>::~framebuffer_attachment()
	{
		glDeleteTextures(1, &m_id);
	}*/



	framebuffer_color_attachment::framebuffer_color_attachment(s_type w, s_type h) :
		mage::gl::texture2d(w, h, nullptr, {}),
		mage::gfx::framebuffer_color_attachment(w, h),
		mage::dimensional<s_type>(w, h)
	{
		init();
		update();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}



	framebuffer_depth_attachment::framebuffer_depth_attachment(s_type w, s_type h) :
		mage::gl::texture2d(w, h, nullptr, {}),
		mage::gfx::framebuffer_depth_attachment(w, h),
		mage::dimensional<s_type>(w, h)
	{
		init();
		update();
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_w, m_h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
	}
}
