#pragma once
#include "pch.h"

namespace magl
{
	class layer final : public coga::layer
	{
	public:
		layer() :
			coga::layer("MAGL"),
			m_map(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr)
		{
			COGA_ERROR("CREATE MAGL LAYER");

			m_shader_program = new mage::shader_program("res/shader/chunk_v.glsl", "res/shader/chunk_f.glsl", true);

			const uint32_t width = COGA_WIN.get_w(), height = COGA_WIN.get_h();
			m_camera = new mage::camera(*this, 1.f * width, 1.f * height, { 0.f, 0.f, 0.f }, 0.f, .2f);

			open_map("res/blah.mage");
		}
		COGA_DCM(layer);
		~layer()
		{
			COGA_ERROR("DELETE MAGL LAYER");
			delete m_map;
			delete m_shader_program;
			delete m_camera;
		}
	public:
		void open_map(const std::string& fp)
		{
			delete m_map;
			coga::input_file in(fp);
			m_map = new mage::map(in);
		}
	private:
		constexpr static float s_camera_zoom_delta = .01f, s_camera_zoom_min = .01f, s_camera_zoom_max = 2.f, s_camera_move_delta = .01f;
	private:
		mage::map* m_map;
		mage::shader_program* m_shader_program;
		mage::camera* m_camera;
	private:
		bool on_app_draw(coga::app_draw_event& e) override
		{
			coga::gfx::renderer::clear();

			// upload camera and draw map
			m_shader_program->bind();
			m_shader_program->set_uniform_mat4(mage::c::shader_camera, m_camera->get_view_projection());
			m_map->draw(coga::timestep(), *m_shader_program);

			return false;
		}
		// TODO smooth
		bool on_key_press(coga::key_press_event& e) override
		{
			glm::vec3 pos = m_camera->get_pos();
			const int c = e.get_code();
			pos.x += ((c == coga::key::D) - (c == coga::key::A)) * s_camera_move_delta;
			pos.y += ((c == coga::key::W) - (c == coga::key::S)) * s_camera_move_delta;
			m_camera->set_pos(pos);
			return true;
		}
		bool on_mouse_scroll(coga::mouse_scroll_event& e) override
		{
			const float z = m_camera->get_zoom();
			m_camera->set_zoom(glm::clamp(z + e.get_y() * s_camera_zoom_delta, s_camera_zoom_min, s_camera_zoom_max));
			return true;
		}
	};
}
