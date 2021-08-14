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


			/*constexpr bool save = false;
			if (save)
			{
				n::sprite_atlas_bank* sab = new n::sprite_atlas_bank();
				n::sprite_bank* sb = new n::sprite_bank();
				n::sprite_bank::handle s = (new n::sprite(sb, sab, "res/sprite/newSprite.sprite"))->get_handle();
				mage::output_file sabf("res/ab.mage"), sbf("res/sb.mage");
				sab->save(sabf);
				sb->save(sbf);
			}
			else
			{
				mage::input_file sabf("res/ab.mage"), sbf("res/sb.mage");
				n::sprite_atlas_bank* sab = new n::sprite_atlas_bank(sabf);
				n::sprite_bank* sb = new n::sprite_bank(sbf);
			}
			exit(0);*/


			n::sprite_bank* sb = new n::sprite_bank();
			n::sprite_atlas_bank* ab = new n::sprite_atlas_bank();
			n::sprite* sprite = new n::sprite(sb, ab, "res/sprite/newSprite.sprite");
			n::chunk* chunk = new n::chunk({ { sprite, { {-.5f, -.5f}, {.5f, .5f} } } });
			m_map = new n::map(ab, sb, { chunk });
			// TODO save/load map
		}
		MAGE_DCM(layer);
		~layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_map;
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
			m_map->draw(n::timestep(), *m_shader_program);

			// draw framebuffer onto screen
			m_framebuffer->draw();
			return false;
		}
	private:
		n::map* m_map;
		n::framebuffer* m_framebuffer;
		n::shader_program* m_shader_program;
		n::camera* m_camera;
		glm::vec3 m_camera_pos;
		float m_camera_rotation, m_camera_zoom;
	};
}
