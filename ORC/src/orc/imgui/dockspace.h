#pragma once
#include "pch.h"
#include "orc/layer/layer.h"
#include "orc/imgui/window/debug_window.h"
#include "orc/imgui/window/game_window.h"
#include "orc/imgui/window/sprite/sprite_window.h"

namespace orc
{
	class dockspace final : public coga::imgui::dockspace
	{
	public:
		dockspace(orc::layer* const layer) :
			coga::imgui::dockspace(c::dockspace_title, c::dockspace_id, s_menus,
				{
					new orc::window::game_window(layer),
					new orc::window::debug_window(layer),
					new orc::window::sprite_window(layer)
				}
			),
			m_layer(layer),
			m_save_path(""),
			m_build_path("")
		{}
	private:
		orc::layer* m_layer;
		mutable std::string m_save_path, m_build_path;
	private:
		void file_open()
		{
			// TODO this is windows-only
			std::string file = COGA_WIN.open_file_dialog("ORC World (*.orc)\0*.orc\0\0");
			if (!file.empty())
			{
				m_layer->open_map(file);
				m_save_path = file;
			}
		}
		void file_save() const
		{
			if (m_save_path.empty())
				file_save_as();
			else
				m_layer->save_map(m_save_path);
		}
		void file_save_as() const
		{
			file_as(&layer::save_map, "ORC World (*.orc)\0*.orc\0\0", ".orc", m_save_path);
		}
		void file_build() const
		{
			if (m_build_path.empty())
				file_build_as();
			else
				m_layer->build_map(m_build_path);
		}
		void file_build_as() const
		{
			file_as(&layer::build_map, "MAGE World (*.mage)\0*.mage\0\0", ".mage", m_build_path);
		}
		void file_exit() const
		{
			COGA_APP.close();
		}
	private:
		const static inline std::vector<menu> s_menus =
		{
			{
				"File",
				{
					{
						{ "Open...", "Ctrl+O", { coga::key::left_control, coga::key::O }, mef(&dockspace::file_open) },
						// this should be before regular save because of its shortcut
						{ "Save As...", "Ctrl+Shift+S", { coga::key::left_control, coga::key::left_shift, coga::key::S }, mef(&dockspace::file_save_as) },
						{ "Save", "Ctrl+S", { coga::key::left_control, coga::key::S }, mef(&dockspace::file_save) }
					},
					{
						{ "Build As...", "Ctrl+Shift+B", { coga::key::left_control, coga::key::left_shift, coga::key::B }, mef(&dockspace::file_build_as) },
						{ "Build", "Ctrl+B", { coga::key::left_control, coga::key::B }, mef(&dockspace::file_build) }
					},
					{
						{ "Exit", "Alt+F4", { coga::key::left_alt, coga::key::f4 }, mef(&dockspace::file_exit) }
					}	
				}
			}
		};
	private:
		template<typename T>
		void file_as(T fn, const char* filter, const std::string& ext, std::string& cache) const
		{
			// TODO this only works on Windows
			std::string file = COGA_WIN.save_file_dialog(filter);
			if (!file.empty())
			{
				if (!file.ends_with(ext))
					file += ext;

				(m_layer->*(fn))(file);

				if (cache.empty())
					cache = file;
			}
		}
	};
}
