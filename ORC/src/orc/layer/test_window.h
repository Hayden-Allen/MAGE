#pragma once
#include "pch.h"
#include "layer.h"

namespace orc
{
	class test_window final : public mage::imgui::window
	{
	public:
		test_window(layer* const layer) :
			mage::imgui::window(c::test_window_title),
			m_layer(layer)
		{}
		N_DCM(test_window);
	private:
		orc::layer* const m_layer;
	private:
		void run(mage::app_draw_event& e) override
		{
			ImGui::Text("%.2fms | %.2ffps", e.get_delta_time(), 1000.f / e.get_delta_time());
			ImGui::NewLine();
			ImGui::DragFloat("camera_rotation", &m_layer->m_camera_rotation, .01f, 0.f, 2 * glm::pi<float>());
		}
	};
}
