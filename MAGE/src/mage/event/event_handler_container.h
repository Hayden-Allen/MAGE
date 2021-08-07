#pragma once
#include "pch.h"
#include "event_handler.h"
#include "mage/util/iterable.h"

namespace mage
{
	class event_handler_container : public iterable<std::vector<event_handler*>>
	{
	public:
		MAGE_DCM(event_handler_container);
		virtual ~event_handler_container() {}


		void dispatch(event& e)
		{
			for (event_handler* const eh : m_list)
				eh->on_event(e);
		}
		void add(event_handler* const e)
		{
			m_list.emplace_back(e);
		}
		void remove(event_handler* const e)
		{
			const auto& it = std::find(begin(), end(), e);
			MAGE_CORE_ASSERT(it != m_list.end(), "Attempted to remove an event_handler from an event_handler_container that does not contain it");
			m_list.erase(it);
		}
	protected:
		event_handler_container() {}
	};
}
