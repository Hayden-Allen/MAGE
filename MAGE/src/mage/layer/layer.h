#pragma once
#include "pch.h"
#include "mage/event/event_handler.h"
#include "mage/event/event_handler_container.h"

namespace mage
{
	/**
	 * Interface for an application layer. Stored in a layer_stack within an application. 
	 */
	class layer :
		public event_handler,
		public event_handler_container
	{
	public:
		MAGE_DCM(layer);
		virtual ~layer() {}


		virtual void on_attach() {}
		virtual void on_detach() {}
		void on_event(event& e) override
		{
			event_handler::on_event(e);
			dispatch(e);
		}
	protected:
#ifndef MAGE_DIST
		std::string m_name;
		layer(const std::string& name) :
			m_name(name)
		{}
#else
		layer() {}
#endif
	};
}
