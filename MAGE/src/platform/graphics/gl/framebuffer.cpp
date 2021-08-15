#include "pch.h"
#include "framebuffer.h"
#include "framebuffer_attachment.h"

namespace mage::gl
{
	framebuffer::framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<mage::gfx::framebuffer_attachment<mage::gl::texture2d, const void* const, const texture_options&>*>& attachments) :
		mage::gfx::framebuffer<mage::gl::texture2d, const void* const, const texture_options&>(c, w, h, attachments)
	{
		MAGE_CORE_TRACE("Create FB {}", m_id);
		update();
	}



	void framebuffer::update()
	{
		glDeleteFramebuffers(1, &m_id);
		glGenFramebuffers(1, &m_id);
		bind();

		for (const auto& a : m_attachments)
		{
			a->reset();
			glFramebufferTexture2D(GL_FRAMEBUFFER, get_framebuffer_attachment_enum(a->get_type()), GL_TEXTURE_2D, a->get_id(), 0);
		}

		MAGE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "OpenGL framebuffer is incomplete");
		unbind();
	}
}
