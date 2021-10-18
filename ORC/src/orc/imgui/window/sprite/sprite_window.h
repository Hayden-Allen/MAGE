#pragma once
#include "pch.h"
#include "orc/layer/layer.h"
#include "file_tree_node.h"

namespace orc::window
{
	class sprite_window final : public coga::imgui::window
	{
	public:
		sprite_window(layer* layer) :
			coga::imgui::window(c::sprite_window_title, { .menus = s_menus }),
			m_layer(layer),
			m_sprite_bank(layer->m_map->get_sprite_bank()),
			m_atlas_bank(layer->m_map->get_atlas_bank()),
			m_root(new file_tree_node("root", m_sprite_bank, m_atlas_bank)),
			m_selected(nullptr)
		{}
		~sprite_window()
		{
			delete m_root;
		}
	private:
		orc::layer* m_layer;
		sprite_bank* m_sprite_bank;
		sprite_atlas_bank* m_atlas_bank;
		file_tree_node* m_root;
		sprite* m_selected;
	private:
		void run(coga::app_draw_event& e) override
		{
			ImGui::Columns(2);

			sprite* result = m_root->draw();
			if (result)
				m_selected = result;

			if (m_selected)
			{
				ImGui::NextColumn();
				ImGui::Text("%u\n", m_selected->get_handle());
			}

			ImGui::Columns(1);
		}
		void file_open()
		{
			std::string path = COGA_WIN.open_file_dialog("MAGE Sprite (*.sprite)\0*.sprite\0\0");
			if (!path.empty())
				m_root->add_file(path);
		}
	private:
		const static inline std::vector<menu> s_menus =
		{
			{
				"File",
				{
					{
						{ "Open...", "Ctrl+O", { coga::key::left_control, coga::key::O }, mef(&sprite_window::file_open) }
					}
				}
			}
		};
	};
}
