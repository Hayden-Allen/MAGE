#pragma once
#include "pch.h"
#include "framebuffer_attachment.h"
#include "render_object.h"
#include "mage/event/event_handler.h"
#include "mage/event/event_handler_container.h"
#include "mage/util/dimensional.h"

namespace mage::gfx
{
	class framebuffer :
		public render_object,
		public event_handler,
		public dimensional<uint32_t>
	{
	public:
		MAGE_DCM(framebuffer);
		virtual ~framebuffer() {}


		static framebuffer* create(event_handler_container& c, s_type w, s_type h, const std::initializer_list<framebuffer_attachment*>& attachments);
		virtual void update() = 0;
		bool on_window_resize(window_resize_event& e) override
		{
			m_w = e.get_w();
			m_h = e.get_h();
			update();

			for (framebuffer_attachment* const a : m_attachments)
			{
				a->m_w = e.get_w();
				a->m_h = e.get_h();
				a->reset();
			}

			return false;
		}
	protected:
		std::vector<framebuffer_attachment*> m_attachments;


		framebuffer(event_handler_container& c, s_type w, s_type h, const std::initializer_list<framebuffer_attachment*>& attachments) :
			dimensional<s_type>(w, h),
			m_attachments(attachments)
		{
			c.add(this);
		}
	};
}
