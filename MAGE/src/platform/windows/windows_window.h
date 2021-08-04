#pragma once
#include "mage/window.h"

namespace mage
{
	class windows_window : public window
	{
	public:
		windows_window(const window_data& data);
		MAGE_DCM(windows_window);
		~windows_window()
		{
			glfwDestroyWindow(m_window);
		}


		void on_update() override;
		void set_vsync(bool enabled) override
		{
			m_data.vsync = enabled;
			glfwSwapInterval(enabled ? 1 : 0);
		}
	private:
		static bool s_glfw_init;
		GLFWwindow* m_window;
	};
}
