#pragma once
#include "pch.h"
#include "event.h"
#include "mage/math/vec2.h"

namespace mage
{
	template<event_type TYPE>
	class MAGE_API window_event : public event<TYPE, event_category::window>
	{
	public:
		MAGE_DCM(window_event);
	protected:
		window_event() {}
	};



	class MAGE_API window_close_event : public window_event<event_type::window_close>
	{
	public:
		window_close_event() {}
		MAGE_DCM(window_close_event);
		MAGE_EVENT_NAME(window_close_event);
	};



	class MAGE_API window_focus_event : public window_event<event_type::window_focus>
	{
	public:
		window_focus_event() {}
		MAGE_DCM(window_focus_event);
		MAGE_EVENT_NAME(window_focus_event);
	};



	class MAGE_API window_unfocus_event : public window_event<event_type::window_unfocus>
	{
	public:
		window_unfocus_event() {}
		MAGE_DCM(window_unfocus_event);
		MAGE_EVENT_NAME(window_unfocus_event);
	};


	template<event_type TYPE>
	class MAGE_API window_vector_event : public window_event<TYPE>, public vec2<int>
	{
	public:
		MAGE_DCM(window_vector_event);
	protected:
		window_vector_event(int x, int y) :
			vec2<int>(x, y)
		{}
	};



	class MAGE_API window_resize_event : public window_vector_event<event_type::window_resize>
	{
	public:
		window_resize_event(int x, int y) :
			window_vector_event(x, y)
		{}
		MAGE_DCM(window_resize_event);
		MAGE_EVENT_NAME(window_resize_event);
	};



	class MAGE_API window_move_event : public window_vector_event<event_type::window_move>
	{
	public:
		window_move_event(int x, int y) :
			window_vector_event(x, y)
		{}
		MAGE_DCM(window_move_event);
		MAGE_EVENT_NAME(window_move_event);
	};
}
