#include "pch.h"
#include "application.h"

namespace mage
{
	application* application::s_instance = nullptr;



	void application::run() const
	{
		app_tick_event tick;
		app_render_event render;
		while (m_running)
		{
			m_window->on_event(tick);
			// traverse from the bottom up
			for (auto layer : m_layer_stack)
			{
				layer->on_event(tick);
				layer->on_event(render);
			}

			m_window->on_event(render);
		}
	}



	application::application(const window_constructor& data) :
		m_running(true)
	{
		MAGE_CORE_ASSERT(s_instance != nullptr, "Cannot create multiple applications");
		s_instance = this;

		m_window = window::create(data);
		m_window->set_event_callback(MAGE_BIND_EVENT_CALLBACK(application::on_event));
	}
	void application::on_event(mage::event& e)
	{
		event_handler::on_event(e);
		// traverse from the top down
		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin() && !e.was_handled();)
			(*--it)->on_event(e);
	}
}
