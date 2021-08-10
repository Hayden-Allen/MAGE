#pragma once
#include "pch.h"
#include "mage/graphics/context.h"

struct GLFWwindow;

namespace mage::gl
{
	class context final : public mage::gfx::context
	{
	public:
		context(void* const host, uint32_t w, uint32_t h, const std::string& title);
		MAGE_DCM(context);
		~context()
		{
			glfwDestroyWindow(get_window<GLFWwindow*>());
		}
	private:
		static bool s_initialized;
	};
}
