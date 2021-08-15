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
		friend class imgui_layer;
	public:
		layer() :
			mage::layer("ORC"),
			m_map(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr),
			m_camera_pos({ 0.f, 0.f, 0.f }),
			m_camera_rotation(0.f),
			m_camera_zoom(1.f)
		{
			MAGE_ERROR("CREATE ORC LAYER");

			m_framebuffer = new n::framebuffer(*this, 1280, 720, "res/shader/fb_v.glsl", "res/shader/fb_f.glsl");

			m_shader_program = new n::shader_program("res/shader/chunk_v.glsl", "res/shader/chunk_f.glsl", true);

			m_camera = new n::camera(*this, 1.6f, .9f, m_camera_pos, m_camera_rotation, m_camera_zoom);


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


			constexpr bool save = false;
			if (save)
			{
				n::sprite_bank* sb = new n::sprite_bank();
				sprite_atlas_bank* ab = new sprite_atlas_bank();
				sprite* s = new sprite(sb, ab, "res/sprite/newSprite.sprite");
				chunk* c = new chunk();
				c->set_tile_at({ 0, 0 }, 0, s);
				m_map = new map(ab, sb, { c });
				mage::output_file out("res/map.orc");
				m_map->save(out);
			}
			else
			{
				mage::input_file in("res/map.orc");
				m_map = new map(in);
			}
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


		bool on_app_draw(mage::app_draw_event& e) override
		{
			// draw onto framebuffer
			m_framebuffer->bind();
			mage::gfx::renderer::clear();

			// update camera values from imgui_layer
			m_camera->set_pos(m_camera_pos);
			m_camera->set_rotation(m_camera_rotation);
			m_camera->set_zoom(m_camera_zoom);

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
	private:
		map* m_map;
		sprite_atlas_bank* m_sab;
		/*n::static_index_buffer* m_ib;
		n::static_vertex_buffer* m_vb;
		n::static_vertex_array* m_va;*/
		n::framebuffer* m_framebuffer;
		n::shader_program* m_shader_program;
		n::camera* m_camera;
		glm::vec3 m_camera_pos;
		float m_camera_rotation, m_camera_zoom;
	};
}
