#pragma once
#include "pch.h"
#include "mage/graphics/context.h"

struct GLFWwindow;

namespace mage::gl
{
	class context final : public mage::gfx::context
	{
	public:
		context(GLFWwindow* window) :
			m_window(window)
		{}
		MAGE_DCM(context);


		void init() override;
		void clear_screen() override;
		void swap_buffers() override;
	private:
		static bool s_initialized;
		GLFWwindow* m_window;
	};
}
