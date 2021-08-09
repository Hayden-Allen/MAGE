#pragma once
#include "pch.h"
#include "mage/graphics/framebuffer.h"

namespace mage::gl
{
	class framebuffer : public mage::gfx::framebuffer
	{
	public:
		framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<mage::gfx::framebuffer_attachment*>& attachments);
		MAGE_DCM(framebuffer);
		~framebuffer();


		void bind() const override;
		void unbind() const override;
		void update() override;
	};
}
