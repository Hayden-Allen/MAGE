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
    uint32_t imgui_layer::s_instance_count = 0;


    imgui_layer::~imgui_layer()
    {
        if (s_instance_count == 0)
            end();
    }


    bool imgui_layer::on_app_tick(app_tick_event& e)
    {
        if (m_instance_id == 0)
        {
            app_tick(e);

            float current = MAGE_CAST(float, glfwGetTime());
            static float last = 0.f;

            ImGuiIO& io = ImGui::GetIO();
            io.DeltaTime = (last == 0.f ? 1.f : current - last);
            last = current;

            ImGui::NewFrame();
        }
        return false;
    }
    bool imgui_layer::on_app_render(app_render_event& e)
    {
        if (m_instance_id == 0)
        {
            ImGuiIO& io = ImGui::GetIO();
            const window& window = application::get().get_window();
            io.DisplaySize = ImVec2(window.get_w<float>(), window.get_h<float>());

            ImGui::Render();

            app_render(e);
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



#ifndef MAGE_DIST
    imgui_layer::imgui_layer(const std::string& name) :
        layer(name),
        m_instance_id(s_instance_count)
    {
        if (s_instance_count == 0)
            init();
    }
#else
    imgui_layer::imgui_layer()
    {
        if (s_instance_count == 0)
            init();
    }
#endif



    void imgui_layer::init()
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
    }
    void imgui_layer::end()
    {
        ImGui::DestroyContext();
    }
}
