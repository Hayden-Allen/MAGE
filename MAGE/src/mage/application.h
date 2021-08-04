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
	class MAGE_API application : public event_handler
	{
	public:
		MAGE_DCM(application);
		~application()
		{
			delete m_window;
		}


		virtual void run() const;
		window& get_window()
		{
			return *m_window;
		}
		const window& get_window() const
		{
			return *m_window;
		}
		static application& get()
		{
			return *s_instance;
		}
	protected:
		bool m_running;
		layer_stack m_layer_stack;
		window* m_window;


		application(const window_constructor& data);


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
		// terminate execution when the window is closed
		bool on_window_close(window_close_event& e) override
		{
			m_running = false;
			return true;
		}
		void on_event(mage::event& e) override;
	private:
		static application* s_instance;
	};


	application* create_application();
}
