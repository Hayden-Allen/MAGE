#pragma once
#include "pch.h"
#include <imgui.h>
#include "coga/event/app_event.h"
#include "coga/io/input.h"
#include "coga/io/input_key.h"

namespace coga::imgui
{
	class window
	{
	public:
		COGA_DCM(window);
	public:
		void render(app_draw_event& e)
		{
			// cleaner window borders
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			window_setup();

			if (ImGui::Begin(m_title.c_str(), (m_closeable ? &m_active : nullptr), m_flags))
			{
				if (m_flags & ImGuiWindowFlags_MenuBar)
					draw_menus();
				run(e);
				ImGui::End();
			}

			ImGui::PopStyleVar(2);
		}
	protected:
		typedef void(window::* menu_entry_fn)();
		template<typename F>
		static menu_entry_fn mef(F fn)
		{
			return (void(window::*)())fn;
		}
		struct menu_entry
		{
			std::string name, shortcut;
			std::vector<key::code> codes;
			menu_entry_fn fn;
		};
		struct menu
		{
			std::string name;
			std::vector<menu_entry> entries;
		};
		struct window_options
		{
			std::vector<menu> menus = {};
			bool closeable = false;
			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		};
	protected:
		std::string m_title;
		bool m_active, m_closeable;
		ImGuiWindowFlags m_flags;
		std::vector<menu> m_menus;
	protected:
		window(std::string title, const window_options& options = {}) :
			m_title(title),
			m_active(true),
			m_closeable(options.closeable),
			m_flags(options.flags),
			m_menus(options.menus)
		{}
	protected:
		virtual void run(app_draw_event& e) = 0;
		virtual void window_setup() {}
		glm::vec2 get_pos() const
		{
			const ImVec2& view = ImGui::GetCursorPos();
			const ImVec2& min = ImGui::GetWindowPos();
			return { min.x + view.x, min.y + view.y };
		}
		/*ImVec2 get_display_pos() const
		{
			const auto& io = ImGui::GetIO();
		}*/
		glm::vec2 get_size() const
		{
			const ImVec2& s = ImGui::GetWindowSize();
			return { s.x, s.y };
		}
		ImVec2 get_display_size() const
		{
			const ImVec2& min = ImGui::GetWindowContentRegionMin(), max = ImGui::GetWindowContentRegionMax();
			return { max.x - min.x, max.y - min.y };
		}
		glm::vec2 get_mouse_pos() const
		{
			const glm::vec2& w = get_pos();
			const ImVec2& m = ImGui::GetMousePos();
			// for some reason horizontal padding is accounted for but vertical padding isn't (or something like that)
			return { m.x - w.x, w.y - m.y + ImGui::GetContentRegionAvail().y };
		}
	private:
		void draw_menus()
		{
			if (ImGui::BeginMenuBar())
			{
				for (const menu& menu : m_menus)
				{
					if (ImGui::BeginMenu(menu.name.c_str()))
					{
						for (const menu_entry& entry : menu.entries)
							if (ImGui::MenuItem(entry.name.c_str(), entry.shortcut.c_str()))
								(this->*entry.fn)();
						ImGui::EndMenu();
					}
					else
						for (const menu_entry& entry : menu.entries)
							if (COGA_IN.are_keys_pressed(entry.codes))
								(this->*entry.fn)();
				}
				ImGui::EndMenuBar();
			}
		}
	};
}
