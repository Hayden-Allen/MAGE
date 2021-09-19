#pragma once
#include "pch.h"
#include "orc/graphics/sprite.h"
#include "orc/world/chunk.h"
#include "orc/world/map.h"

namespace orc
{
	class imgui_layer;
	namespace window
	{
		class game;
		class debug;
		class sprite;
	}

	class layer final : public coga::layer
	{
		friend class window::game;
		friend class window::debug;
		friend class window::sprite;
	public:
		layer() :
			coga::layer("ORC"),
			m_vm(new mage::sasm::vm()),
			m_script(new mage::sasm::script("res/script/test.sasm", m_vm)),
			m_map(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr)
		{
			COGA_ERROR("CREATE ORC LAYER");

			const uint32_t width = COGA_WIN.get_w(), height = COGA_WIN.get_h();
			m_framebuffer = new mage::framebuffer(*this, width, height, "res/shader/fb_v.glsl", "res/shader/fb_f.glsl");

			m_shader_program = new mage::shader_program("res/shader/chunk_v.glsl", "res/shader/chunk_f.glsl", true);

			m_camera = new mage::camera(*this, 1.f * width, 1.f * height, { 0.f, 0.f, 0.f }, 0.f, .2f);

			sprite_atlas_bank* sab = new sprite_atlas_bank();
			m_sb = new sprite_bank();
			new sprite(m_sb, sab, "res/sprite/big.sprite");
			m_map = new map(sab, m_sb);


			m_vm = new mage::sasm::vm();
			m_script = new mage::sasm::script("res/script/test.sasm", m_vm);
			hasl::sasm::script_runtime rt = { 0.f, 0.f, nullptr, {} };
			m_vm->run(*m_script, rt, { 0.f, 0.f });
			m_vm->mem_dump();
		}
		COGA_DCM(layer);
		~layer()
		{
			COGA_ERROR("DELETE ORC LAYER");
			delete m_vm;
			delete m_script;
			delete m_map;
			delete m_framebuffer;
			delete m_shader_program;
			delete m_camera;
		}
	public:
		void open_map(const std::string& fp)
		{
			delete m_map;
			coga::input_file in(fp);
			m_map = new map(in);
			m_sb = m_map->get_sprite_bank();
		}
		void save_map(const std::string& fp)
		{
			coga::output_file out(fp);
			m_map->save(out);
		}
		void build_map(const std::string& fp)
		{
			coga::output_file out(fp);
			m_map->build(out);
		}
	private:
		constexpr static float s_camera_zoom_delta = .01f, s_camera_zoom_min = .01f, s_camera_zoom_max = 2.f, s_camera_move_delta = .1f;
	private:
		mage::sasm::vm* m_vm;
		mage::sasm::script* m_script;
		sprite_bank* m_sb;
		map* m_map;
		mage::framebuffer* m_framebuffer;
		mage::shader_program* m_shader_program;
		mage::camera* m_camera;
	private:
		bool on_app_draw(coga::app_draw_event& e) override
		{
			// draw onto framebuffer
			m_framebuffer->bind();
			coga::gfx::renderer::clear();

			// upload camera and draw map
			m_shader_program->bind();
			m_shader_program->set_uniform_mat4(mage::c::shader_camera, m_camera->get_view_projection());
			m_map->draw(coga::timestep(), *m_shader_program);

			// draw framebuffer onto screen
			m_framebuffer->draw();


			/*hasl::sasm::script_runtime rt = { e.get_time(), e.get_delta_time(), nullptr, {} };
			m_vm->run(*m_script, rt, { 0.f, 0.f });*/


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
