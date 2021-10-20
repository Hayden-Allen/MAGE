#pragma once
#include "pch.h"
#include "orc/layer/layer.h"
#include "file_tree_node.h"

namespace orc::window
{
	class sprite_window final : public coga::imgui::window
	{
		friend class game_window;
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

			sprite* selected = m_root->draw();
			if (selected)
				m_selected = selected;

			ImGui::NextColumn();

			if(m_selected)
				ImGui::Text("%d\n", m_selected->get_handle());

			ImGui::Columns(1);
		}
		void file_open()
		{
			// platform independent; implemented in respective *_window.cpp
			const char separator_token = COGA_WIN.get_multi_file_separator_token();

			std::string path = COGA_WIN.open_multi_file_dialog("MAGE Sprite (*.sprite)\0*.sprite\0\0");
			size_t separator = path.find(separator_token);

			// multiple files
			if (separator != std::string::npos)
			{
				// path of the directory that selected files are in
				std::string dir = path.substr(0, separator) + c::file_tree_separator_token;
				while (separator != std::string::npos)
				{
					// index of next separator token
					const size_t next_separator = path.find(separator_token, separator + 1);
					// sanitized index (for use in substr)
					const size_t end = std::min(next_separator, path.size());

					// add file at path `<base_dir>/<file_name>`
					m_root->add_file(dir + path.substr(separator + 1, end - separator - 1));
					
					// advance to next file
					separator = next_separator;
				}
			}
			// single file
			else if (!path.empty())
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
