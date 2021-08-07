#pragma once
#include "pch.h"
#include "mage/layer/layer.h"

namespace mage
{
	/**
	 * Interface for platform-specific imgui implementations
	 */
	class imgui_layer : public layer
	{
	public:
		MAGE_DCM(imgui_layer);
		virtual ~imgui_layer();


		bool on_app_tick(app_tick_event& e) final override;
		bool on_app_render(app_render_event& e) final override;
		virtual bool on_key_press(key_press_event& e) override;
		virtual bool on_key_release(key_release_event& e) override;
		// overriding both this and on_key_press results in characters being typed twice
		// virtual bool on_key_type(key_type_event& e) override;
		virtual bool on_mouse_press(mouse_press_event& e) override;
		virtual bool on_mouse_release(mouse_release_event& e) override;
		virtual bool on_mouse_move(mouse_move_event& e) override;
		virtual bool on_mouse_scroll(mouse_scroll_event& e) override;
		virtual bool on_window_resize(window_resize_event& e) override;
		virtual void on_key_base(key_event& e, bool pressed);
	protected:
		static uint32_t s_instance_count;
		uint32_t m_instance_id;


	#ifndef MAGE_DIST
		imgui_layer(const std::string& name = "imgui");
	#else
		imgui_layer();
	#endif


		virtual void app_tick(app_tick_event& e) const = 0;
		virtual void app_render(app_render_event& e) const = 0;
	private:
		static int s_imgui_min_charcode;
		static int s_imgui_max_charcode;


		static void init();
		static void end();
	};
}
