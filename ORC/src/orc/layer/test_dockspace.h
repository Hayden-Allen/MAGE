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
			)
		{}
	private:
		void dockspace_run(mage::app_draw_event& e) override
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						mage::application::get().close();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
		}
	};
}
