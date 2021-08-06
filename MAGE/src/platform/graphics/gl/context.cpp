#include "pch.h"
#include "context.h"
#include "mage/log.h"

namespace mage::gl
{
	bool context::s_initialized = false;

	

	void context::init()
	{
		MAGE_CORE_ASSERT(!s_initialized, "Cannot initialize GLFW more than once");
		s_initialized = true;

		glfwMakeContextCurrent(m_window);
		bool success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MAGE_CORE_ASSERT(success, "Failed to initialize glad")
	}
	void context::clear_screen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void context::swap_buffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}
