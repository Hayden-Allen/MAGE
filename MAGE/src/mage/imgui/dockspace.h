#pragma once
#include "pch.h"
#include "window.h"
#include "mage/event/app_event.h"
#include "mage/application.h"

namespace mage::imgui
{
	class dockspace : public window
	{
	public:
		MAGE_DCM(dockspace);
		virtual ~dockspace()
		{
			for (window* const w : m_windows)
				delete w;
		}
	protected:
		std::vector<window*> m_windows;
		std::string m_id;
	protected:
		dockspace(const std::string& name, const std::string& id, const std::initializer_list<window*>& windows) :
			window(name, false, s_flags),
			m_windows(windows),
			m_id(id)
		{}
	protected:
		virtual void dockspace_run(app_draw_event& e) = 0;
	private:
		constexpr static ImGuiWindowFlags s_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	private:
		void run(app_draw_event& e) override
		{
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID(m_id.c_str());
				ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_None);
			}

			dockspace_run(e);

			for (window* const w : m_windows)
				w->render(e);
		}
		void window_setup() override
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
		}
	};
}