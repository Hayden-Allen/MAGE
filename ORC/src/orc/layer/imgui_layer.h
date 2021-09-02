#pragma once
#include "pch.h"
#include "test_dockspace.h"

namespace orc
{
	class imgui_layer final : public coga::imgui::windows_layer
	{
	public:
		imgui_layer(orc::layer* const layer) :
			coga::imgui::windows_layer("ORC ImGui"),
			m_test_dockspace(layer)
		{
			COGA_ERROR("CREATE ORC IMGUI LAYER");
		}
		COGA_DCM(imgui_layer);
		~imgui_layer()
		{
			COGA_ERROR("DELETE ORC IMGUI LAYER");
		}
	public:
		bool on_app_draw(coga::app_draw_event& e) override
		{
			m_test_dockspace.render(e);
			return false;
		}
	private:
		test_dockspace m_test_dockspace;
	};
}
