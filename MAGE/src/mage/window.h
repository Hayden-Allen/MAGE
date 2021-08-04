#pragma once
#include "pch.h"
#include "event/event.h"
#include "math/dimensional.h"
#include "math/color.h"

namespace mage
{
	struct window_data
	{
		std::string title;
		uint32_t width, height;
		bool vsync;
		color<float> clear;

		window_data(const std::string& t, uint32_t w, uint32_t h, bool v, color<float> c) :
			title(t),
			width(w),
			height(h),
			vsync(v),
			clear(c)
		{}
	};



	class window : public dimensional<uint32_t>
	{
	public:
		MAGE_DCM(window);
		virtual ~window() {}


		static window* create(const window_data& data);
		virtual void on_update() = 0;
		virtual void set_vsync(bool enabled) = 0;
		const std::string& get_title() const
		{
			return m_data.title;
		}
		bool is_vsync() const
		{
			return m_data.vsync;
		}
	protected:
		window_data m_data;


		window(const window_data& data) :
			dimensional<uint32_t>(data.width, data.height),
			m_data(data)
		{}
	};
}

