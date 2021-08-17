#pragma once
#include "pch.h"
#include <imgui.h>
#include "mage/event/app_event.h"

namespace mage::imgui
{
	class window
	{
	public:
		MAGE_DCM(window);
	public:
		void render(app_draw_event& e)
		{
			// cleaner window borders
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			window_setup();

			if (ImGui::Begin(m_title.c_str(), (m_closeable ? &m_active : nullptr), m_flags))
			{
				run(e);
				ImGui::End();
			}

			ImGui::PopStyleVar(2);
		}
	protected:
		bool m_active, m_closeable;
		std::string m_title;
		ImGuiWindowFlags m_flags;
	protected:
		window(std::string title, bool closeable = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None) :
			m_title(title),
			m_closeable(closeable),
			m_flags(flags)
		{}
	protected:
		virtual void run(app_draw_event& e) = 0;
		virtual void window_setup() {}
		ImVec2 get_pos() const
		{
			ImVec2 view = ImGui::GetCursorPos();
			ImVec2 min = ImGui::GetWindowPos();
			return { min.x + view.x, min.y + view.y };
		}
		ImVec2 get_size() const
		{
			return ImGui::GetContentRegionAvail();
		}
		glm::vec2 get_mouse_pos() const
		{
			ImVec2 w = get_pos(), m = ImGui::GetMousePos();
			return { m.x - w.x, w.y - m.y };
		}
	};
}
