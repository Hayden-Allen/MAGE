#include "pch.h"
#include "framebuffer.h"
#include "framebuffer_attachment.h"

namespace mage::gfx
{
	framebuffer* framebuffer::create(event_handler_container& c, s_type w, s_type h, const std::initializer_list<framebuffer_attachment*>& attachments)
	{
		return new mage::gl::framebuffer(c, w, h, attachments);
	}
}



namespace mage::gl
{
	framebuffer::framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<mage::gfx::framebuffer_attachment*>& attachments) :
		mage::gfx::framebuffer(c, w, h, attachments)
	{
		update();
	}
	framebuffer::~framebuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}



	void framebuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	}
	void framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void framebuffer::update()
	{
		glGenFramebuffers(1, &m_id);
		bind();

		for (const auto& a : m_attachments)
		{
			a->update();
			glFramebufferTexture2D(GL_FRAMEBUFFER, get_framebuffer_attachment_enum(a->get_type()), GL_TEXTURE_2D, a->get_id(), 0);
		}

		MAGE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "OpenGL framebuffer is incomplete");
		unbind();
	}
}
