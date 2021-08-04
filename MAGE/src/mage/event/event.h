#pragma once
#include "pch.h"

// used for convenience when implementing event classes
#define MAGE_EVENT_TYPE(type) \
	virtual const char* get_name() const override { return #type; } \
	virtual event_type get_type() const override { return type; } \
	static event_type get_static_type() { return type; }
#define MAGE_EVENT_CATEGORIES(categories) \
	virtual uint32_t get_categories() const override { return categories; }

namespace mage
{
	enum class event_type
	{
		none = 0,
		app_tick, app_update, app_render,
		key_press, key_release,
		mouse_press, mouse_release, mouse_move, mouse_scroll,
		window_close, window_resize, window_focus, window_unfocus, window_move
	};
	// these need to behave like ints, so they can't be an enum class. I still want them scoped though
	namespace event_category
	{
		enum ec
		{
			none = 0,
			input = MAGE_BIT(0),
			keyboard = MAGE_BIT(1),
			mouse = MAGE_BIT(2),
			mouse_button = MAGE_BIT(3),
			app = MAGE_BIT(4),
			window = MAGE_BIT(5)
		};
	}



	class MAGE_API event
	{
		template<typename T>
		using dispatch_fn = std::function<bool(T&)>;
	public:
		MAGE_DCM(event);


		virtual event_type get_type() const = 0;
		virtual uint32_t get_categories() const = 0;
		// these will only be used to print debug messages
	#ifndef MAGE_DIST
		virtual const char* get_name() const = 0;
		virtual std::string to_string() const
		{
			return get_name();
		}
	#endif
		// whether or not this event is in the given category
		bool is(event_category::ec c)
		{
			return get_categories() & MAGE_CAST(uint32_t, c);
		}
		// if this event's type matches the given type, call the given function with it
		template<typename T>
		bool dispatch(dispatch_fn<T> fn)
		{
			if (get_type() == T::get_static_type())
			{
				m_handled = fn(MAGE_PUN(T, *this));
				return true;
			}
			return false;
		}
	protected:
		bool m_handled;


		event() : m_handled(false) {}
	};
}
