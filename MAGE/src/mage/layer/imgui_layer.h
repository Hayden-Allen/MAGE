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
		static int s_imgui_min_charcode;
		static int s_imgui_max_charcode;
		

		bool on_app_tick(app_tick_event& e) override;
		bool on_app_render(app_render_event& e) override;
		bool on_key_press(key_press_event& e) override;
		bool on_key_release(key_release_event& e) override;
		bool on_key_type(key_type_event& e) override;
		bool on_mouse_press(mouse_press_event& e) override;
		bool on_mouse_release(mouse_release_event& e) override;
		bool on_mouse_move(mouse_move_event& e) override;
		bool on_mouse_scroll(mouse_scroll_event& e) override;
		bool on_window_resize(window_resize_event& e) override;
		void on_key_base(key_event& e, bool pressed);
	};
}
