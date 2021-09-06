#pragma once
#include "pch.h"
#include "orc/layer/layer.h"

namespace orc::window
{
	class sprite final : public coga::imgui::window
	{
	public:
		sprite(layer* const layer) :
			coga::imgui::window(c::sprite_window_title),
			m_layer(layer)
		{}
	private:
		orc::layer* const m_layer;
	private:
		void run(coga::app_draw_event& e) override
		{
			auto sprites = m_layer->m_sb;

			for (sprite_bank::handle i = sprite_bank::s_first; i < sprites->get_last(); i++)
				ImGui::Text("%u\n", sprites->get(i)->get_handle());
			ImGui::Text("TEST");
		}
	};
}
