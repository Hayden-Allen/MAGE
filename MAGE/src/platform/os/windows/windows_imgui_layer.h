#pragma once
#include "pch.h"
#include "mage/imgui/imgui_layer.h"

namespace mage
{
	/**
	 * Windows implementation of the imgui_layer interface
	 */
	class windows_imgui_layer : public imgui_layer
	{
	public:
	#ifndef MAGE_DIST
		windows_imgui_layer(const std::string& name = "Windows ImGui Layer");
	#else
		windows_imgui_layer();
	#endif
		MAGE_DCM(windows_imgui_layer);
		~windows_imgui_layer();
	protected:
		void app_tick(app_tick_event& e) const final override;
		void app_render(app_render_event& e) const final override;
	};
}
