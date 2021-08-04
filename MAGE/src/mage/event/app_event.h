#pragma once
#include "pch.h"
#include "event.h"

namespace mage
{
	template<event_type TYPE>
	class MAGE_API app_event : public event<TYPE, event_category::app>
	{
	public:
		MAGE_DCM(app_event);
	protected:
		app_event() {}
	};



	class MAGE_API app_tick_event : public app_event<event_type::app_tick>
	{
	public:
		app_tick_event();
		MAGE_DCM(app_tick_event);
		MAGE_EVENT_NAME(app_tick_event);
	};



	class MAGE_API app_update_event : public app_event<event_type::app_update>
	{
	public:
		app_update_event();
		MAGE_DCM(app_update_event);
		MAGE_EVENT_NAME(app_update_event);
	};



	class MAGE_API app_render_event : public app_event<event_type::app_render>
	{
	public:
		app_render_event();
		MAGE_DCM(app_render_event);
		MAGE_EVENT_NAME(app_render_event);
	};
}
