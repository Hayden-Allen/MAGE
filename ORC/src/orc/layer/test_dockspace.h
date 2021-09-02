#pragma once
#include "pch.h"
#include "layer.h"
#include "game_window.h"
#include "test_window.h"

namespace orc
{
	class test_dockspace final : public coga::imgui::dockspace
	{
	public:
		test_dockspace(orc::layer* const layer) :
			coga::imgui::dockspace(c::test_dockspace_title, c::test_dockspace_id, s_menus,
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
		void file_open()
		{
			// TODO windows format
			std::string file = COGA_WIN.open_file_dialog("ORC World (*.orc)\0*.orc\0\0");
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
			// TODO windows format
			std::string file = COGA_WIN.save_file_dialog("ORC World (*.orc)\0*.orc\0\0");
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
			void(window:: * fn)() = (void(window::*)())&test_dockspace::file_open;
			COGA_APP.close();
		}
	private:
		const static inline std::vector<menu> s_menus =
		{
			{
				"File",
				{
					{ "Open...", "Ctrl+O", { coga::key::left_control, coga::key::O }, mef(&test_dockspace::file_open) },
					// this should be before regular save because of its shortcut
					{ "Save As...", "Ctrl+Shift+S", { coga::key::left_control, coga::key::left_shift, coga::key::S }, mef(&test_dockspace::file_save_as) },
					{ "Save", "Ctrl+S", { coga::key::left_control, coga::key::S }, mef(&test_dockspace::file_save) },
					{ "Exit", "Alt+F4", { coga::key::left_alt, coga::key::f4 }, mef(&test_dockspace::file_exit) }
				}
			}
		};
	};
}
