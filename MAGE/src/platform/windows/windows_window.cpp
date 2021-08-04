#include "pch.h"
#include "windows_window.h"
#include "log.h"

namespace mage
{
	window* window::create(const window_data& data)
	{
		return new windows_window(data);
	}



	bool windows_window::s_glfw_init = false;
	windows_window::windows_window(const window_data& data) :
		window(data)
	{
		MAGE_CORE_INFO("Creating window {} <{}, {}>", m_data.title, m_w, m_h);

		if (!s_glfw_init)
		{
			bool success = glfwInit();
			MAGE_CORE_ASSERT(success, "Failed to initialize GLFW");
			s_glfw_init = true;
		}

		m_window = glfwCreateWindow(MAGE_CAST(int, m_w), MAGE_CAST(int, m_h), m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);

		set_vsync(m_data.vsync);
		glClearColor(data.clear.r, data.clear.g, data.clear.b, 1.f);
	}


	void windows_window::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}
