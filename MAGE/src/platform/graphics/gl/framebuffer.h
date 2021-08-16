#pragma once
#include "pch.h"
#include "texture.h"
#include "mage/graphics/framebuffer.h"

namespace mage::gl
{
	class framebuffer : public mage::gfx::framebuffer<mage::gl::texture2d, const void* const, const texture_options&>
	{
	public:
		framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<mage::gfx::framebuffer_attachment<mage::gl::texture2d, const void* const, const texture_options&>*>& attachments);
		MAGE_DCM(framebuffer);
		virtual ~framebuffer()
		{
			MAGE_CORE_TRACE("Delete FB {}", m_id);
			glDeleteFramebuffers(1, &m_id);
		}
	public:
		void update() override;
		void bind() const override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}
		void unbind() const override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	};
}
