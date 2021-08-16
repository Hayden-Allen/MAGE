#include "pch.h"
#include "windows_layer.h"
#include "mage/application.h"

namespace mage::imgui
{
	#ifndef MAGE_DIST
	windows_layer::windows_layer(const std::string& name) :
		mage::imgui::layer(name)
	{
		if(s_instance_count == 0)
		{
			ImGui_ImplGlfw_InitForOpenGL(MAGE_CAST(GLFWwindow*, application::get().get_window().get_native_window()), true);
			ImGui_ImplOpenGL3_Init("#version 410");
		}
		s_instance_count++;
	}
	#else
	windows_layer::windows_layer()
	{
		if (s_instance_count == 0)
		{
			ImGui_ImplGlfw_InitForOpenGL(MAGE_CAST(GLFWwindow*, application::get().get_window().get_native_window()), true);
			ImGui_ImplOpenGL3_Init("#version 410");
}
		s_instance_count++;
	}
	#endif
	windows_layer::~windows_layer()
	{
		s_instance_count--;
		if (s_instance_count == 0)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
		}
	}



	void windows_layer::app_tick(app_tick_event& e) const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}
	void windows_layer::app_render(app_render_event& e) const
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* ctx = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(ctx);
		}
	}
}
