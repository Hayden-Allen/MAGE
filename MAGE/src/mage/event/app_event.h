#pragma once
#include "pch.h"
#include "event.h"

namespace mage
{
	/**
	 * Base
	 */
	class MAGE_API app_event : public event
	{
	public:
		MAGE_DCM(app_event);
		MAGE_EVENT_CATEGORIES(event_category::app);
	protected:
		app_event() {}
	};



	/**
	 * Implementation
	 */
	class MAGE_API app_tick_event : public app_event
	{
	public:
		app_tick_event();
		MAGE_DCM(app_tick_event);
		MAGE_EVENT_TYPE(event_type::app_tick);
	};
	class MAGE_API app_update_event : public app_event
	{
	public:
		app_update_event();
		MAGE_DCM(app_update_event);
		MAGE_EVENT_TYPE(event_type::app_update);
	};
	class MAGE_API app_render_event : public app_event
	{
	public:
		app_render_event();
		MAGE_DCM(app_render_event);
		MAGE_EVENT_TYPE(event_type::app_render);
	};
}
