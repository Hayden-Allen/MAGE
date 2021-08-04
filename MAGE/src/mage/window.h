#pragma once
#include "pch.h"
#include "event/event.h"
#include "event/event_handler.h"
#include "event/event_propagator.h"
#include "util/dimensional.h"
#include "util/color.h"

namespace mage
{
	// just to make parameters cleaner
	struct window_constructor
	{
		std::string title;
		uint32_t w, h;
		bool vsync;
		color<float> clear;
	};



	/**
	 * Interface for a non-mobile OS window
	 */
	class MAGE_API window : public event_handler, public event_propagator, public positional<uint32_t>, public dimensional<uint32_t>
	{
	public:
		MAGE_DCM(window);
		virtual ~window() {}


		static window* create(const window_constructor& c);
		virtual void set_vsync(bool enabled) = 0;
		const std::string& get_title() const
		{
			return m_title;
		}
		bool is_vsync() const
		{
			return m_vsync;
		}
	protected:
		std::string m_title;
		bool m_vsync;
		color<float> m_clear;


		window(const window_constructor& c) :
			positional<uint32_t>(0, 0),
			dimensional<uint32_t>(c.w, c.h),
			m_title(c.title),
			m_vsync(c.vsync),
			m_clear(c.clear)
		{}
	};
}

