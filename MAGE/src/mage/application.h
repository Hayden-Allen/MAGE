#pragma once
#include "pch.h"
#include "event/event_handler.h"
#include "event/window_event.h"
#include "log.h"
#include "window.h"

namespace mage
{
	/**
	 * Main driver class. Must be implemented in the client.
	 */
	class application : public event_handler
	{
	public:
		MAGE_DCM(application);
		~application()
		{
			delete m_window;
		}


		virtual void run() const = 0;
	protected:
		window* m_window;
		bool m_running;


		application(const window_constructor& data) :
			m_running(true)
		{
			m_window = window::create(data);
			m_window->set_event_callback(MAGE_BIND_EVENT_CALLBACK(application::on_event));
		}


		// terminate execution when the window is closed
		bool on_window_close(window_close_event& e) override
		{
			m_running = false;
			return true;
		}
	};


	application* create_application();
}
