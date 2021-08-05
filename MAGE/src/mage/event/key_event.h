#pragma once
#include "pch.h"
#include "event.h"

namespace mage
{
	/**
	 * Base
	 */
	class key_event : public event
	{
	public:
		MAGE_DCM(key_event);


		MAGE_EVENT_CATEGORIES(event_category::input | event_category::keyboard);
		int get_code() const
		{
			return m_code;
		}
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": " << m_code;
			return ss.str();
		}
	protected:
		int m_code;


		key_event(int code) :
			m_code(code)
		{}
	};


	
	/**
	 * Implementation
	 */
	class key_press_event : public key_event
	{
	public:
		key_press_event(int code, bool repeat) :
			key_event(code),
			m_repeat(repeat)
		{}
		MAGE_DCM(key_press_event);


		MAGE_EVENT_TYPE(event_type::key_press);
		bool is_repeat() const
		{
			return m_repeat;
		}
		std::string to_string() const override
		{
			std::stringstream ss;
			ss << this->get_name() << ": " << m_code << " | " << std::boolalpha << m_repeat;
			return ss.str();
		}
	private:
		bool m_repeat;
	};
	class key_release_event : public key_event
	{
	public:
		key_release_event(int code) :
			key_event(code)
		{}
		MAGE_DCM(key_release_event);
		MAGE_EVENT_TYPE(event_type::key_release);
	};
	class key_type_event : public key_event
	{
	public:
		key_type_event(int code) :
			key_event(code)
		{}
		MAGE_DCM(key_type_event);
		MAGE_EVENT_TYPE(event_type::key_type);
	};
}
