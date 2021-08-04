#pragma once
#include "pch.h"
#include "layer.h"

namespace mage
{
	class MAGE_API imgui_layer : public layer
	{
	public:
		imgui_layer() :
		#ifndef MAGE_DIST
			layer("imgui")
		#else
			layer()
		#endif
		{}
		MAGE_DCM(imgui_layer);


		void on_attach() override;
		void on_detach() override;
	private:
		bool on_app_tick(app_tick_event& e) override;
		bool on_app_render(app_render_event& e) override;
	};
}
