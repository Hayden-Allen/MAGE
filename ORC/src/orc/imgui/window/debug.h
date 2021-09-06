#pragma once
#include "pch.h"
#include "orc/layer/layer.h"

namespace orc::window
{
	class debug final : public coga::imgui::window
	{
	public:
		debug(layer* const layer) :
			coga::imgui::window(c::debug_window_title),
			m_layer(layer)
		{}
		COGA_DCM(debug);
	private:
		orc::layer* const m_layer;
	private:
		void run(coga::app_draw_event& e) override
		{
			ImGui::Text("%.2fms | %.2ffps", e.get_delta_time(), 1000.f / e.get_delta_time());
		}
	};
}
