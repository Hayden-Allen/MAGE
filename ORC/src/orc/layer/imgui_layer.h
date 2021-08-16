#pragma once
#include "pch.h"
#include "test_dockspace.h"

namespace orc
{
	class imgui_layer final : public mage::imgui::windows_layer
	{
	public:
		imgui_layer(orc::layer* const layer) :
			mage::imgui::windows_layer("ORC ImGui"),
			m_test_dockspace(layer)
		{
			MAGE_ERROR("CREATE ORC IMGUI LAYER");
		}
		MAGE_DCM(imgui_layer);
		~imgui_layer()
		{
			MAGE_ERROR("DELETE ORC IMGUI LAYER");
		}
	public:
		bool on_app_draw(mage::app_draw_event& e) override
		{
			m_test_dockspace.render(e);
			return false;
		}
	private:
		test_dockspace m_test_dockspace;
	};
}
