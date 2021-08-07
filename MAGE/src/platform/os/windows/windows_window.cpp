#include "pch.h"
#include "windows_window.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/window_event.h"
#include "log.h"
#include "platform/graphics/gl/context.h"

namespace mage
{
	/**
	 * Windows implementation; called by application()
	 */
	window* window::create(const window_constructor& data)
	{
		return new windows_window(data);
	}



	bool windows_window::s_glfw_init = false;



	windows_window::windows_window(const window_constructor& data) :
		window(data)
	{
		// initialize GLFW if it hasn't been already
		if (!s_glfw_init)
		{
			bool success = glfwInit();
			MAGE_CORE_ASSERT(success, "Failed to initialize GLFW");
			s_glfw_init = true;
		}

		// create window and make it the current context
		m_window = glfwCreateWindow(MAGE_CAST(int, m_w), MAGE_CAST(int, m_h), m_title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_window, this);

		// initialize graphics context
		m_context = new gl::context(m_window);
		m_context->init();

		// window settings
		set_vsync(m_vsync);
		glClearColor(m_clear.r, m_clear.g, m_clear.b, 1.f);

		// callbacks
		glfwSetErrorCallback(error_callback);
		glfwSetCharCallback(m_window, char_callback);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, mouse_move_callback);
		glfwSetScrollCallback(m_window, mouse_scroll_callback);
		glfwSetWindowCloseCallback(m_window, window_close_callback);
		glfwSetWindowFocusCallback(m_window, window_focus_callback);
		glfwSetWindowPosCallback(m_window, window_move_callback);
		glfwSetWindowSizeCallback(m_window, window_size_callback);
	}



	/**
	 * GLFW callbacks
	 */
#define WIN MAGE_CAST(windows_window*, glfwGetWindowUserPointer(window))
	void windows_window::error_callback(int code, const char* desc)
	{
		MAGE_CORE_ERROR("[GLFW Error {}]: {}", code, desc);
	}
	void windows_window::char_callback(GLFWwindow* window, uint32_t code)
	{
		key_type_event e(MAGE_CAST(int, code));
		WIN->invoke(e);
	}
	void windows_window::key_callback(GLFWwindow* window, int key, int scan, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			key_press_event e(key, action == GLFW_REPEAT);
			WIN->invoke(e);
		}
		else if (action == GLFW_RELEASE)
		{
			key_release_event e(key);
			WIN->invoke(e);
		}
	}
	void windows_window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			mouse_press_event e(button);
			WIN->invoke(e);
		}
		else if (action == GLFW_RELEASE)
		{
			mouse_release_event e(button);
			WIN->invoke(e);
		}
	}
	void windows_window::mouse_move_callback(GLFWwindow* window, double x, double y)
	{
		mouse_move_event e(MAGE_CAST(float, x), MAGE_CAST(float, y));
		WIN->invoke(e);
	}
	void windows_window::mouse_scroll_callback(GLFWwindow* window, double x, double y)
	{
		mouse_scroll_event e(MAGE_CAST(float, x), MAGE_CAST(float, y));
		WIN->invoke(e);
	}
	void windows_window::window_close_callback(GLFWwindow* window)
	{
		window_close_event e;
		WIN->invoke(e);
	}
	void windows_window::window_focus_callback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			window_focus_event e;
			WIN->invoke(e);
		}
		else
		{
			window_unfocus_event e;
			WIN->invoke(e);
		}
	}
	void windows_window::window_move_callback(GLFWwindow* window, int x, int y)
	{
		WIN->m_x = MAGE_CAST(positional::s_type, x);
		WIN->m_y = MAGE_CAST(positional::s_type, y);

		window_move_event e(x, y);
		WIN->invoke(e);
	}
	void windows_window::window_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		WIN->m_w = MAGE_CAST(dimensional::s_type, width);
		WIN->m_h = MAGE_CAST(dimensional::s_type, height);

		window_resize_event e(width, height);
		WIN->invoke(e);
	}
#undef WIN
}
