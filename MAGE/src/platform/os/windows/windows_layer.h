#pragma once
#include "pch.h"
#include "mage/imgui/layer.h"

namespace mage::imgui
{
	/**
	 * Windows implementation of the imgui_layer interface
	 */
	class windows_layer : public layer
	{
	public:
	#ifndef MAGE_DIST
		windows_layer(const std::string& name = "Windows ImGui Layer");
	#else
		windows_layer();
	#endif
		MAGE_DCM(windows_layer);
		~windows_layer();
	protected:
		void app_tick(app_tick_event& e) const final override;
		void app_render(app_render_event& e) const final override;
	};
}
