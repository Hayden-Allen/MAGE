#pragma once
#include "pch.h"
#include "orc/graphics/sprite.h"
#include "orc/world/chunk.h"
#include "orc/world/map.h"

namespace orc
{
	class imgui_layer;

	class layer final : public mage::layer
	{
		friend class game_window;
		friend class test_window;
	public:
		layer() :
			mage::layer("ORC"),
			m_map(nullptr),
			m_sprite(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr),
			m_camera_rotation(0.f)
		{
			MAGE_ERROR("CREATE ORC LAYER");

			auto& window = mage::application::get().get_window();
			const uint32_t width = window.get_w(), height = window.get_h();
			m_framebuffer = new n::framebuffer(*this, width, height, "res/shader/fb_v.glsl", "res/shader/fb_f.glsl");

			m_shader_program = new n::shader_program("res/shader/chunk_v.glsl", "res/shader/chunk_f.glsl", true);

			m_camera = new n::camera(*this, 1.f * width, 1.f * height, { 0.f, 0.f, 0.f }, m_camera_rotation, .2f);


			/*uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
			m_ib = new n::static_index_buffer(indices, 1);
			float vertices[] =
			{
				0.f, 0.f, 0.f, 0.f, 0.f,
				1.f, 0.f, 0.05f, 0.f, 0.f,
				1.f, 1.f, 0.05f, 0.05f, 0.f,
				0.f, 1.f, 0.f, 0.05f, 0.f
			};
			m_vb = new n::static_vertex_buffer(vertices, 20);
			m_va = new n::static_vertex_array(m_vb, { mage::gfx::shader_type::float2, mage::gfx::shader_type::float2, mage::gfx::shader_type::float1 });*/


			/*constexpr bool save = false;
			if (save)
			{
				m_sab = new sprite_atlas_bank();
				n::sprite_bank* sb = new n::sprite_bank();
				n::sprite_bank::handle s = (new sprite(sb, m_sab, "res/sprite/newSprite.sprite"))->get_handle();
				mage::output_file sabf("res/ab.mage"), sbf("res/sb.mage");
				m_sab->save(sabf);
				sb->save(sbf);
			}
			else
			{
				mage::input_file sabf("res/ab.mage"), sbf("res/sb.mage");
				m_sab = new sprite_atlas_bank(sabf);
				n::sprite_bank* sb = new n::sprite_bank(sbf);
			}*/


			sprite_bank* sb = new sprite_bank();
			sprite_atlas_bank* ab = new sprite_atlas_bank();
			// m_sprite = new sprite(sb, ab, "res/sprite/newSprite2.sprite");
			constexpr bool save = false;
			if (save)
			{
				m_map = new map(ab, sb);
			}
			else
			{
				mage::input_file in("res/map.orc");
				m_map = new map(in);
			}
			m_sprite = new sprite(sb, ab, "res/sprite/small.sprite");
		}
		MAGE_DCM(layer);
		~layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_map;
			/*delete m_sab;
			delete m_ib;
			delete m_vb;
			delete m_va;*/
			delete m_framebuffer;
			delete m_shader_program;
			delete m_camera;
		}
	private:
		constexpr static float s_camera_zoom_delta = .01f, s_camera_zoom_min = .01f, s_camera_zoom_max = 2.f, s_camera_move_delta = .1f;
	private:
		map* m_map;
		sprite* m_sprite;
		sprite_atlas_bank* m_sab;
		/*n::static_index_buffer* m_ib;
		n::static_vertex_buffer* m_vb;
		n::static_vertex_array* m_va;*/
		n::framebuffer* m_framebuffer;
		n::shader_program* m_shader_program;
		n::camera* m_camera;
		float m_camera_rotation;
	private:
		bool on_app_draw(mage::app_draw_event& e) override
		{
			// draw onto framebuffer
			m_framebuffer->bind();
			mage::gfx::renderer::clear();

			// update camera values from imgui_layer
			m_camera->set_rotation(m_camera_rotation);

			// upload camera and draw map
			m_shader_program->bind();
			m_shader_program->set_uniform_mat4(n::c::shader_camera, m_camera->get_view_projection());
			m_map->draw(mage::timestep(), *m_shader_program);
			/*m_sab->get(0)->bind(0);
			mage::gfx::renderer::draw(m_ib, m_va);*/

			// draw framebuffer onto screen
			m_framebuffer->draw();
			return false;
		}
		bool on_key_press(mage::key_press_event& e) override
		{
			glm::vec3 pos = m_camera->get_pos();
			const int c = e.get_code();
			pos.x += ((c == mage::key::D) - (c == mage::key::A)) * s_camera_move_delta;
			pos.y += ((c == mage::key::W) - (c == mage::key::S)) * s_camera_move_delta;
			m_camera->set_pos(pos);
			return true;
		}
		bool on_mouse_scroll(mage::mouse_scroll_event& e) override
		{
			const float z = m_camera->get_zoom();
			m_camera->set_zoom(glm::clamp(z + e.get_y() * s_camera_zoom_delta, s_camera_zoom_min, s_camera_zoom_max));
			return true;
		}
	};
}
