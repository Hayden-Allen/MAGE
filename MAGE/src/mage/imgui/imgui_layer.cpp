#include "pch.h"
#include "imgui_layer.h"
#include "input/input_key.h"
#include "util/functions.h"
#include "application.h"
#include "log.h"

namespace mage
{
    int imgui_layer::s_imgui_min_charcode = 1;
    int imgui_layer::s_imgui_max_charcode = 0xffff;



    void imgui_layer::on_attach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.f;
        }

        ImGui_ImplGlfw_InitForOpenGL(MAGE_CAST(GLFWwindow*, application::get().get_window().get_native_window()), true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    void imgui_layer::on_detach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }



	bool imgui_layer::on_app_tick(app_tick_event& e)
	{
        float current = MAGE_CAST(float, glfwGetTime());
        static float last = 0.f;

        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = (last == 0.f ? 1.f : current - last);
        last = current;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        return false;
	}
    bool imgui_layer::on_app_render(app_render_event& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        const window& window = application::get().get_window();
        io.DisplaySize = ImVec2(window.get_w<float>(), window.get_h<float>());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* ctx = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(ctx);
        }
        return false;
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

        io.KeyCtrl = io.KeysDown[mage::key::left_control] || io.KeysDown[mage::key::right_control];
        io.KeyShift = io.KeysDown[mage::key::left_shift] || io.KeysDown[mage::key::right_shift];
        io.KeyAlt = io.KeysDown[mage::key::left_alt] || io.KeysDown[mage::key::right_alt];
    #ifdef MAGE_PLATFORM_WINDOWS
        io.KeySuper = false;
    #else
        io.KeySuper = io.KeysDown[mage::key::left_super] || io.KeysDown[mage::key::right_super];
    #endif
    }
}
