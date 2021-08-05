#pragma once
#include "pch.h"
#include "mage/event/event_handler.h"

namespace mage
{
	/**
	 * Interface for an application layer. Stored in a layer_stack within an application. 
	 */
	class MAGE_API layer : public event_handler
	{
	public:
		MAGE_DCM(layer);
		virtual ~layer() {}


		virtual void on_attach() {}
		virtual void on_detach() {}
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