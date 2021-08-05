#pragma once
#include "mage/window.h"

namespace mage
{
	/**
	 * Windows implementation of the window interface using GLFW
	 */
	class windows_window final : public window
	{
	public:
		windows_window(const window_constructor& data);
		MAGE_DCM(windows_window);
		~windows_window()
		{
			glfwDestroyWindow(m_window);
		}

		void* get_native_window() const override;
		void set_vsync(bool enabled) override
		{
			glfwSwapInterval((m_vsync = enabled) ? 1 : 0);
		}
	private:
		static bool s_glfw_init;
		GLFWwindow* m_window;


		bool on_app_tick(app_tick_event& e) override;
		bool on_app_render(app_render_event& e) override;
		// GLFW callback functions
		static void error_callback(int code, const char* desc);
		static void char_callback(GLFWwindow* window, uint32_t code);
		static void key_callback(GLFWwindow* window, int key, int scan, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void mouse_move_callback(GLFWwindow* window, double x, double y);
		static void mouse_scroll_callback(GLFWwindow* window, double x, double y);
		static void window_close_callback(GLFWwindow* window);
		static void window_focus_callback(GLFWwindow* window, int focused);
		static void window_move_callback(GLFWwindow* window, int x, int y);
		static void window_size_callback(GLFWwindow* window, int width, int height);
	};
}
