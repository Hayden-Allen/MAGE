#pragma once
#include "pch.h"
#include "event.h"
#include "mage/math/vec2.h"

namespace mage
{
	template<event_type TYPE, int CATEGORIES = event_category::none>
	class MAGE_API mouse_event : public event<TYPE, event_category::input | event_category::mouse | CATEGORIES>, public vec2<float>
	{
	public:
		MAGE_DCM(mouse_event);


		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": <" << m_x << ", " << m_y << ">";
			return ss.str();
		}
	protected:
		mouse_event(float x, float y) :
			vec2<float>(x, y)
		{}
	};



	class MAGE_API mouse_move_event : public mouse_event<event_type::mouse_move>
	{
	public:
		MAGE_DCM(mouse_move_event);
		MAGE_EVENT_NAME(mouse_move);
	};



	class MAGE_API mouse_scroll_event : public mouse_event<event_type::mouse_scroll>
	{
	public:
		MAGE_DCM(mouse_scroll_event);
		MAGE_EVENT_NAME(mouse_scroll);
	};



	template<event_type TYPE>
	class MAGE_API mouse_button_event : public mouse_event<TYPE, event_category::mouse_button>
	{
	public:
		MAGE_DCM(mouse_button_event);


		int get_button() const
		{
			return m_button;
		}
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": <" << this->m_x << ", " << this->m_y << "> | " << m_button;
			return ss.str();
		}
	protected:
		int m_button;


		mouse_button_event(float x, float y, int button) :
			mouse_event<TYPE, event_category::mouse_button>(x, y),
			m_button(button)
		{}
	};



	class MAGE_API mouse_press_event : public mouse_button_event<event_type::mouse_press>
	{
	public:
		mouse_press_event(float x, float y, int button) :
			mouse_button_event<event_type::mouse_press>(x, y, button)
		{}
		MAGE_DCM(mouse_press_event);
		MAGE_EVENT_NAME(mouse_press_event);
	};



	class MAGE_API mouse_release_event : public mouse_button_event<event_type::mouse_release>
	{
	public:
		mouse_release_event(float x, float y, int button) :
			mouse_button_event<event_type::mouse_release>(x, y, button)
		{}
		MAGE_DCM(mouse_release_event);
		MAGE_EVENT_NAME(mouse_release_event);
	};
}
