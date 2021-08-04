#pragma once
#include "pch.h"
#include "event/app_event.h"
#include "event/event_handler.h"
#include "event/window_event.h"
#include "layer/layer_stack.h"
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


		virtual void run() const
		{
			app_tick_event e;
			while (m_running)
			{
				m_window->on_event(e);
				// traverse from the bottom up
				for (auto layer : m_layer_stack)
					layer->on_event(e);
			}
		}
	protected:
		bool m_running;
		layer_stack m_layer_stack;
		window* m_window;


		application(const window_constructor& data) :
			m_running(true)
		{
			m_window = window::create(data);
			m_window->set_event_callback(MAGE_BIND_EVENT_CALLBACK(application::on_event));
		}


		/**
		 * Simple wrappers for the layer_stack
		 */
		void attach_layer(layer* const layer)
		{
			m_layer_stack.attach(layer);
		}
		void detach_layer(layer* const layer)
		{
			m_layer_stack.detach(layer);
		}
		void on_event(mage::event& e) override
		{
			event_handler::on_event(e);
			// traverse from the top down
			for (auto it = m_layer_stack.end(); it != m_layer_stack.begin() && !e.was_handled();)
				(*--it)->on_event(e);
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
