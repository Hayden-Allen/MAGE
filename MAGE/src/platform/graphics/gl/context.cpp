#include "pch.h"
#include "context.h"
#include "mage/log.h"

namespace mage::gfx
{
	context* context::create(void* const host, uint32_t w, uint32_t h, const std::string& title)
	{
		return new mage::gl::context(host, w, h, title);
	}
	size_t context::get_max_texture_units()
	{
		int i;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &i);
		return MAGE_CAST(size_t, i);
	}
}



namespace mage::gl
{
	static void error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* user)
	{
		if(severity == GL_DEBUG_SEVERITY_HIGH)
			MAGE_CORE_ERROR("[GL Error {}]: {}", id, msg);
	}



	bool context::s_initialized = false;

	

	context::context(void* const host, uint32_t w, uint32_t h, const std::string& title)
	{
		MAGE_CORE_ASSERT(!s_initialized, "Cannot initialize GLFW more than once");
		s_initialized = true;

		bool success = glfwInit();
		MAGE_CORE_ASSERT(success, "Failed to initialize GLFW");

		m_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
		GLFWwindow* const win = MAGE_CAST(GLFWwindow*, m_window);
		glfwSetWindowUserPointer(win, host);

		glfwMakeContextCurrent(win);
		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MAGE_CORE_ASSERT(success, "Failed to initialize glad");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(error_callback, nullptr);
	}
}
