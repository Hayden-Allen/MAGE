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
			const auto& size = get_display_size();
			m_layer->m_camera->set_size(size.x, size.y);

			const auto& win = mage::application::get().get_window();
			ImGui::Image(ImTextureID(m_layer->m_framebuffer->get_color_attachment_id()), size, { 0.f, 1.f }, { 1.f, 0.f });

			if (ImGui::IsWindowHovered())
			{
				const glm::mat4& cam = glm::inverse(m_layer->m_camera->get_view_projection());

				// get mouse pos in OpenGL screen space [-1, 1]
				glm::vec2 mouse = get_mouse_pos();
				const auto& size = get_display_size();
				mouse = mage::range(-1.f, 1.f).map_from(mouse, { 0.f, size.x }, { 0.f, size.y });

				const glm::ivec4 world_mouse = cam * glm::vec4(mouse, 0.f, 1.f);

				if (world_mouse.x >= 0 && world_mouse.y >= 0)
				{
					if (mage::input::get().is_mouse_pressed(0))
						m_layer->m_map->set_tile_at(world_mouse, 0, nullptr);
					else if (mage::input::get().is_mouse_pressed(mage::mouse::button::right))
						m_layer->m_map->delete_tile_at(world_mouse, 0);
				}
			}
		}
	};
}
