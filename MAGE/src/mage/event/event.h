#pragma once
#include "pch.h"

#define MAGE_EVENT_NAME(type) \
	virtual const char* get_name() const { return #type; }

namespace mage
{
	enum class event_type
	{
		none = 0,
		window_close, window_resize, window_focus, window_unfocus, window_move,
		app_tick, app_update, app_render,
		key_press, key_release,
		mouse_press, mouse_release, mouse_move, mouse_scroll
	};
	enum event_category
	{
		none		 = 0,
		input		 = MAGE_BIT(0),
		keyboard	 = MAGE_BIT(1),
		mouse		 = MAGE_BIT(2),
		mouse_button = MAGE_BIT(3),
		app			 = MAGE_BIT(4),
		window		 = MAGE_BIT(5)
	};



	template<event_type TYPE, int CATEGORIES>
	class MAGE_API event
	{
		template<typename T>
		using dispatch_fn = std::function<bool(T&)>;
	public:
		event() : m_handled(false) {}
		MAGE_DCM(event);


	#ifndef MAGE_DIST
		virtual const char* get_name() const = 0;
		virtual std::string to_string() const
		{
			return get_name();
		}
	#endif
		event_type get_type() const
		{
			return TYPE;
		}
		uint32_t get_categories() const
		{
			return CATEGORIES;
		}
		bool is(event_category c)
		{
			return get_categories() & MAGE_CAST(uint32_t, c);
		}
		template<typename T>
		bool dispatch(dispatch_fn<T> fn)
		{
			if (TYPE == T::get_static_type())
			{
				m_handled = fn(MAGE_CAST(T, *this));
				return true;
			}
			return false;
		}
	protected:
		bool m_handled;


		static event_type get_static_type()
		{
			return TYPE;
		}
	};
}
