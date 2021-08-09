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
			m_framebuffer(nullptr),
			m_vertex_array(nullptr),
			m_vertex_buffer(nullptr),
			m_index_buffer(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr),
			m_rect_color({ 0.f, 0.f, 0.f }),
			m_camera_pos({ 0.f, 0.f, 0.f }),
			m_camera_rotation(0.f),
			m_camera_zoom(1.f)
		{
			MAGE_ERROR("CREATE ORC LAYER");

			m_framebuffer = new n::framebuffer(*this, 1280, 720, "res/framebuffer_vertex.glsl", "res/framebuffer_fragment.glsl");

			uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
			m_index_buffer = new n::static_index_buffer(indices, mage::arrlen(indices));
			float vertices[] =
			{
				-.5f, -.5f,
				 .5f, -.5f,
				 .5f,  .5f,
				-.5f,  .5f
			};
			m_vertex_buffer = new n::static_vertex_buffer(vertices, mage::arrlen(vertices));
			m_vertex_array = new n::static_vertex_array(m_vertex_buffer, { mage::gfx::shader_type::float2 });
		

			m_shader_program = new n::shader_program("res/v.glsl", "res/f.glsl");


			m_camera = new n::camera(*this, 1.6f, .9f, m_camera_pos, m_camera_rotation, m_camera_zoom);
		}
		MAGE_DCM(layer);
		~layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_framebuffer;
			delete m_vertex_array;
			delete m_vertex_buffer;
			delete m_index_buffer;
			delete m_shader_program;
			delete m_camera;
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			// draw on to framebuffer
			m_framebuffer->bind();
			e.get_renderer().clear();

			m_camera->set_pos(m_camera_pos);
			m_camera->set_rotation(m_camera_rotation);
			m_camera->set_zoom(m_camera_zoom);

			m_shader_program->bind();
			m_shader_program->set_uniform_float3("u_color", m_rect_color);
			m_shader_program->set_uniform_mat4("u_view_projection", m_camera->get_view_projection());

			e.get_renderer().draw(m_index_buffer, m_vertex_array);

			m_framebuffer->unbind();

			// draw framebuffer onto screen
			m_framebuffer->draw(e.get_renderer());

			return false;
		}
	private:
		n::framebuffer* m_framebuffer;
		n::static_vertex_array* m_vertex_array;
		n::static_vertex_buffer* m_vertex_buffer;
		n::static_index_buffer* m_index_buffer;
		n::shader_program* m_shader_program;
		n::camera* m_camera;
		glm::vec3 m_rect_color, m_camera_pos;
		float m_camera_rotation, m_camera_zoom;
	};
}
