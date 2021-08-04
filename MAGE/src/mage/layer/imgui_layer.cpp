#include "pch.h"
#include "imgui_layer.h"
#include "util/functions.h"
#include "application.h"
#include "log.h"
#include "platform/OpenGL/imgui_renderer.h"

namespace mage
{
    int imgui_layer::s_imgui_min_charcode = 1;
    int imgui_layer::s_imgui_max_charcode = 0xffff;



	void imgui_layer::on_attach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// temporary keycodes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
	}
	void imgui_layer::on_detach()
	{
        ImGui_ImplOpenGL3_Shutdown();
	}



	bool imgui_layer::on_app_tick(app_tick_event& e)
	{
        float current = MAGE_CAST(float, glfwGetTime());
        static float last = 0.f;

        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = (last == 0.f ? 1.f : current - last);
        last = current;
        const window& win = application::get().get_window();
        io.DisplaySize = ImVec2(win.get_w<float>(), win.get_h<float>());



        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        return true;
	}
    bool imgui_layer::on_app_render(app_render_event& e)
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return true;
    }
    bool imgui_layer::on_key_press(key_press_event& e)
    {
        on_key_base(e, true);
        return false;
    }
    bool imgui_layer::on_key_release(key_release_event& e)
    {
        on_key_base(e, false);
        return false;
    }
    bool imgui_layer::on_key_type(key_type_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        int c = e.get_code();
        if(c >= s_imgui_min_charcode && c <= s_imgui_max_charcode)
            io.AddInputCharacter(c);

        return false;
    }
    bool imgui_layer::on_mouse_press(mouse_press_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        int b = e.get_button();
        if(b >= 0 && b < ImGuiMouseButton_COUNT)
            io.MouseDown[e.get_button()] = true;

        return false;
    }
    bool imgui_layer::on_mouse_release(mouse_release_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        int b = e.get_button();
        if (b >= 0 && b < ImGuiMouseButton_COUNT)
            io.MouseDown[e.get_button()] = false;

        return false;
    }
    bool imgui_layer::on_mouse_move(mouse_move_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MousePos = ImVec2(e.get_x<float>(), e.get_y<float>());

        return false;
    }
    bool imgui_layer::on_mouse_scroll(mouse_scroll_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.MouseWheel += e.get_y();
        io.MouseWheelH += e.get_x();

        return false;
    }
    bool imgui_layer::on_window_resize(window_resize_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(e.get_w<float>(), e.get_h<float>());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

        return false;
    }
    void imgui_layer::on_key_base(key_event& e, bool pressed)
    {
        ImGuiIO& io = ImGui::GetIO();

        int c = e.get_code();
        if (c >= 0 && c < arrlen(io.KeysDown))
            io.KeysDown[c] = pressed;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    #ifdef MAGE_PLATFORM_WINDOWS
        io.KeySuper = false;
    #else
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    #endif
    }
}
