#pragma once
#include "pch.h"
#include <imgui.h>
#include "layer.h"

namespace orc
{
	class imgui_layer final : public mage::windows_imgui_layer
	{
	public:
		imgui_layer(orc::layer* const layer) :
			mage::windows_imgui_layer("ORC ImGui"),
			m_layer(layer)
		{
			MAGE_ERROR("CREATE ORC IMGUI LAYER");
		}
		MAGE_DCM(imgui_layer);
		~imgui_layer()
		{
			MAGE_ERROR("DELETE ORC IMGUI LAYER");
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			static bool open = true;
			if (open)
			{
				if (ImGui::Begin("Test", &open))
				{
					ImGui::Text("%.2fms | %.2ffps", e.get_delta_time(), 1000.f / e.get_delta_time());
					ImGui::NewLine();
					ImGui::DragInt("sprite_frame", &m_layer->m_sprite_frame, 1.f, 0, 1);
					ImGui::NewLine();
					ImGui::ColorPicker3("rect_color", &m_layer->m_rect_color[0]);
					ImGui::NewLine();
					ImGui::DragFloat2("camera_pos", &m_layer->m_camera_pos[0], .01f, -2.f, 2.f);
					ImGui::NewLine();
					ImGui::DragFloat("camera_rotation", &m_layer->m_camera_rotation, .01f, 0.f, 2 * glm::pi<float>());
					ImGui::NewLine();
					ImGui::DragFloat("camera_zoom", &m_layer->m_camera_zoom, .01f, .1f, 10.f);
					ImGui::NewLine();

					const auto& win = mage::application::get().get_window();
					ImGui::Image((void*)m_layer->m_framebuffer->get_color_attachment_id(), { win.get_w<float>(), win.get_h<float>() });
				}
				ImGui::End();
			}

			return false;
		}
	private:
		orc::layer* const m_layer;
	};
}
