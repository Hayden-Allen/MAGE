#pragma once
#include "pch.h"
#include "layer.h"
#include "game_window.h"
#include "test_window.h"

namespace orc
{
	class test_dockspace final : public mage::imgui::dockspace
	{
	public:
		test_dockspace(orc::layer* const layer) :
			mage::imgui::dockspace(c::test_dockspace_title, c::test_dockspace_id,
				{
					new game_window(layer),
					new test_window(layer)
				}
			),
			m_layer(layer),
			m_last_path("")
		{}
	private:
		orc::layer* m_layer;
		mutable std::string m_last_path;
	private:
		void dockspace_run(mage::app_draw_event& e) override
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open...", "Ctrl+O"))
						file_open();
					else if (ImGui::MenuItem("Save", "Ctrl+S"))
						file_save();
					else if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
						file_save_as();

					ImGui::Separator();

					if (ImGui::MenuItem("Exit"))
						file_exit();

					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			if (mage::input::get().are_keys_pressed(mage::key::O, mage::key::left_control))
				file_open();
			if (mage::input::get().are_keys_pressed(mage::key::S, mage::key::left_control, mage::key::left_shift))
				file_save_as();
			else if (mage::input::get().are_keys_pressed(mage::key::S, mage::key::left_control))
				file_save();
		}
		void file_open() const
		{
			std::string file = MAGE_WIN.open_file_dialog("ORC World (*.orc)\0*.orc\0\0");
			if (!file.empty())
			{
				m_layer->open_map(file);
				m_last_path = file;
			}
		}
		void file_save() const
		{
			if (m_last_path.empty())
				file_save_as();
			else
				m_layer->save_map(m_last_path);
		}
		void file_save_as() const
		{
			std::string file = MAGE_WIN.save_file_dialog("ORC World (*.orc)\0*.orc\0\0");
			if (!file.empty())
			{
				if (!file.ends_with(".orc"))
					file += ".orc";
				m_layer->save_map(file);
				if (m_last_path.empty())
					m_last_path = file;
			}
		}
		void file_exit() const
		{
			mage::application::get().close();
		}
	};
}
