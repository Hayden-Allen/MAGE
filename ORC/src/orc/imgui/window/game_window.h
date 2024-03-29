#pragma once
#include "pch.h"
#include "orc/layer/layer.h"
#include "sprite/sprite_window.h"

namespace orc::window
{
	class game_window final : public coga::imgui::window
	{
	public:
		game_window(layer* const layer, const sprite_window* const sprites) :
			coga::imgui::window(c::game_window_title),
			m_layer(layer),
			m_selected(&sprites->m_selected)
		{}
	public:
	private:
		orc::layer* const m_layer;
		const sprite*const* m_selected;
	private:
		void run(coga::app_draw_event& e) override
		{
			const auto& size = get_display_size();
			m_layer->m_camera->set_size(size.x, size.y);
			ImGui::Image(ImTextureID(m_layer->m_framebuffer->get_color_attachment_id()), size, { 0.f, 1.f }, { 1.f, 0.f });

			if (ImGui::IsWindowHovered())
			{
				const glm::mat4& cam = glm::inverse(m_layer->m_camera->get_view_projection());

				// get mouse pos in OpenGL screen space [-1, 1]
				glm::vec2 mouse = get_mouse_pos();
				const auto& size = get_display_size();
				mouse = coga::range(-1.f, 1.f).map_from(mouse, { 0.f, std::max(1.f, size.x) }, { 0.f, std::max(1.f, size.y) });

				const glm::ivec4 world_mouse = cam * glm::vec4(mouse, 0.f, 1.f);

				// if in bounds
				if (*m_selected && world_mouse.x >= 0 && world_mouse.y >= 0)
				{
					if (COGA_IN.is_mouse_left())
						m_layer->m_map->set_tile_at(world_mouse, 0, *m_selected);
					else if (COGA_IN.is_mouse_right())
						m_layer->m_map->delete_tile_at(world_mouse, 0);
				}
			}
		}
	};
}
