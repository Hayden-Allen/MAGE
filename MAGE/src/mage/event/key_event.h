#pragma once
#include "pch.h"
#include "event.h"

namespace mage
{
	template<event_type TYPE>
	class MAGE_API key_event : public event<TYPE, event_category::input | event_category::keyboard>
	{
	public:
		MAGE_DCM(key_event);


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



	class MAGE_API key_press_event : public key_event<event_type::key_press>
	{
	public:
		key_press_event(int code, bool repeat) :
			key_event<event_type::key_press>(code),
			m_repeat(repeat)
		{}
		MAGE_DCM(key_press_event);


		MAGE_EVENT_NAME(key_press_event);
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



	class MAGE_API key_release_event : public key_event<event_type::key_release>
	{
	public:
		key_release_event(int code) :
			key_event<event_type::key_release>(code)
		{}
		MAGE_DCM(key_release_event);
		MAGE_EVENT_NAME(key_release_event);
	};
}
