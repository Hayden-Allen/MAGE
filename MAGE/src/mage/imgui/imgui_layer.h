#pragma once
#include "pch.h"
#include "mage/layer/layer.h"

namespace mage
{
	class imgui_layer : public layer
	{
	public:
#ifndef MAGE_DIST
		imgui_layer(const std::string& name = "imgui") :
			layer(name) {}
		#else
		imgui_layer() {}
		#endif
		MAGE_DCM(imgui_layer);


		virtual void on_attach() override;
		virtual void on_detach() override;
	protected:
		virtual bool on_app_tick(app_tick_event& e) override;
		virtual bool on_app_draw(app_draw_event& e) override;
		virtual bool on_app_render(app_render_event& e) override;
		virtual bool on_key_press(key_press_event& e) override;
		virtual bool on_key_release(key_release_event& e) override;
		virtual bool on_key_type(key_type_event& e) override;
		virtual bool on_mouse_press(mouse_press_event& e) override;
		virtual bool on_mouse_release(mouse_release_event& e) override;
		virtual bool on_mouse_move(mouse_move_event& e) override;
		virtual bool on_mouse_scroll(mouse_scroll_event& e) override;
		virtual bool on_window_resize(window_resize_event& e) override;
		virtual void on_key_base(key_event& e, bool pressed);
	private:
		static int s_imgui_min_charcode;
		static int s_imgui_max_charcode;
	};
}
