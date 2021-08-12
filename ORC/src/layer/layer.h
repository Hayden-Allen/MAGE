#pragma once
#include "pch.h"

namespace orc
{
	class layer final : public mage::layer
	{
		friend class imgui_layer;
	public:
		layer() :
			mage::layer("ORC"),
			m_sprite_bank(nullptr),
			m_sprite(0),
			m_atlas_bank(nullptr),
			m_framebuffer(nullptr),
			m_vertex_array(nullptr),
			m_vertex_buffer(nullptr),
			m_index_buffer(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr),
			m_camera_pos({ 0.f, 0.f, 0.f }),
			m_camera_rotation(0.f),
			m_camera_zoom(1.f)
		{
			MAGE_ERROR("CREATE ORC LAYER");

			m_framebuffer = new n::framebuffer(*this, 1280, 720, "res/shader/fb_v.glsl", "res/shader/fb_f.glsl");

			uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
			m_index_buffer = new n::static_index_buffer(indices, mage::arrlen(indices));
		

			m_shader_program = new n::shader_program("res/shader/texture_v.glsl", "res/shader/texture_f.glsl");
			m_shader_program->set_uniform_int("u_texture", 0);


			m_camera = new n::camera(*this, 1.6f, .9f, m_camera_pos, m_camera_rotation, m_camera_zoom);


			constexpr bool save = false;
			if (save)
			{
				m_atlas_bank = new n::sprite_atlas_bank();
				m_sprite_bank = new n::sprite_bank();
				m_sprite = m_sprite_bank->add(new n::sprite(m_atlas_bank, "res/sprite/newSprite.sprite"));
				mage::output_file ab("res/ab.mage"), sb("res/sb.mage");
				m_atlas_bank->save(ab);
				m_sprite_bank->save(sb);
			}
			else
			{
				mage::input_file ab("res/ab.mage"), sb("res/sb.mage");
				m_atlas_bank = new n::sprite_atlas_bank(ab);
				m_sprite_bank = new n::sprite_bank(sb);
			}


			const auto& [x, y] = m_sprite_bank->get(m_sprite)->get_base_coords();
			float vertices[] =
			{
				-.5f, -.5f, x.get_min(), y.get_min(),
				 .5f, -.5f,	x.get_max(), y.get_min(),
				 .5f,  .5f,	x.get_max(), y.get_max(),
				-.5f,  .5f,	x.get_min(), y.get_max()
			};
			m_vertex_buffer = new n::static_vertex_buffer(vertices, mage::arrlen(vertices));
			m_vertex_array = new n::static_vertex_array(m_vertex_buffer, { mage::gfx::shader_type::float2, mage::gfx::shader_type::float2 });
		}
		MAGE_DCM(layer);
		~layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_atlas_bank;
			delete m_framebuffer;
			delete m_vertex_array;
			delete m_vertex_buffer;
			delete m_index_buffer;
			delete m_shader_program;
			delete m_camera;
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			// draw onto framebuffer
			m_framebuffer->bind();
			mage::gfx::renderer::clear();

			m_camera->set_pos(m_camera_pos);
			m_camera->set_rotation(m_camera_rotation);
			m_camera->set_zoom(m_camera_zoom);

			m_shader_program->bind();
			m_sprite_bank->get(m_sprite)->update(n::time());
			m_shader_program->set_uniform_float2("u_offset", m_sprite_bank->get(m_sprite)->get_current_frame().offset);
			m_shader_program->set_uniform_mat4("u_view_projection", m_camera->get_view_projection());

			m_atlas_bank->get(0)->bind(0);
			mage::gfx::renderer::draw(m_index_buffer, m_vertex_array);

			// draw framebuffer onto screen
			m_framebuffer->draw();
			return false;
		}
	private:
		n::sprite_bank* m_sprite_bank;
		n::sprite_bank::handle m_sprite;
		n::sprite_atlas_bank* m_atlas_bank;
		n::framebuffer* m_framebuffer;
		n::static_vertex_array* m_vertex_array;
		n::static_vertex_buffer* m_vertex_buffer;
		n::static_index_buffer* m_index_buffer;
		n::shader_program* m_shader_program;
		n::camera* m_camera;
		glm::vec3 m_camera_pos;
		float m_camera_rotation, m_camera_zoom;
	};
}
