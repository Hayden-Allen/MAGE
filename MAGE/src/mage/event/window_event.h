#pragma once
#include "pch.h"
#include "event.h"
#include "mage/util/positional.h"
#include "mage/util/dimensional.h"

namespace mage
{
	/**
	 * Base
	 */
	class MAGE_API window_event : public event
	{
	public:
		MAGE_DCM(window_event);
		MAGE_EVENT_CATEGORIES(event_category::window);
	protected:
		window_event() {}
	};



	/**
	 * Implementation
	 */
	class MAGE_API window_close_event : public window_event
	{
	public:
		window_close_event() {}
		MAGE_DCM(window_close_event);
		MAGE_EVENT_TYPE(event_type::window_close);
	};
	class MAGE_API window_focus_event : public window_event
	{
	public:
		window_focus_event() {}
		MAGE_DCM(window_focus_event);
		MAGE_EVENT_TYPE(event_type::window_focus);
	};
	class MAGE_API window_unfocus_event : public window_event
	{
	public:
		window_unfocus_event() {}
		MAGE_DCM(window_unfocus_event);
		MAGE_EVENT_TYPE(event_type::window_unfocus);
	};
	class MAGE_API window_resize_event : public window_event, public dimensional<int>
	{
	public:
		window_resize_event(int x, int y) :
			dimensional<int>(x, y)
		{}
		MAGE_DCM(window_resize_event);


		MAGE_EVENT_TYPE(event_type::window_resize);
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << get_name() << ": <" << m_w << ", " << m_h << ">";
			return ss.str();
		}
	};
	class MAGE_API window_move_event : public window_event, public positional<int>
	{
	public:
		window_move_event(int x, int y) :
			positional<int>(x, y)
		{}
		MAGE_DCM(window_move_event);


		MAGE_EVENT_TYPE(event_type::window_move);
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << get_name() << ": <" << m_x << ", " << m_y << ">";
			return ss.str();
		}
	};
}
