#pragma once
#include "pch.h"
#include "layer.h"

namespace orc
{
	class game_window final : public mage::imgui::window
	{
	public:
		game_window(layer* const layer) :
			mage::imgui::window(c::game_window_title),
			m_layer(layer)
		{}
	private:
		orc::layer* const m_layer;
	private:
		void run(mage::app_draw_event& e) override
		{
			const auto& win = mage::application::get().get_window();
			ImGui::Image((void*)m_layer->m_framebuffer->get_color_attachment_id(), get_size(), { 0.f, 1.f }, { 1.f, 0.f });
		}
	};
}
