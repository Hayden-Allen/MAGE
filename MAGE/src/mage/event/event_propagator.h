#pragma once
#include "pch.h"
#include "event.h"

namespace mage
{
	typedef std::function<void(event&)> event_callback_t;



	/**
	 * An object that creates and sends events to an event_handler
	 */
	class event_propagator
	{
	public:
		MAGE_DCM(event_propagator);


		void invoke(event& e)
		{
			m_callback(e);
		}
		void set_event_callback(event_callback_t callback)
		{
			m_callback = callback;
		}
	protected:
		event_callback_t m_callback;


		event_propagator() {}
	};
}
