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
			m_vertex_array(nullptr),
			m_vertex_buffer(nullptr),
			m_index_buffer(nullptr),
			m_shader_program(nullptr),
			m_camera(nullptr),
			m_rect_color({ 0.f, 0.f, 0.f }),
			m_camera_pos({ 0.f, 0.f, 0.f })
		{
			MAGE_ERROR("CREATE ORC LAYER");


			uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
			m_index_buffer = mage::gfx::index_buffer::create_static(indices, mage::arrlen(indices));
			float vertices[] =
			{
				-.5f, -.5f,
				 .5f, -.5f,
				 .5f,  .5f,
				-.5f,  .5f
			};
			m_vertex_buffer = mage::gfx::vertex_buffer::create_static(vertices, mage::arrlen(vertices));
			m_vertex_array = mage::gfx::vertex_array::create_static(m_vertex_buffer, { mage::gfx::shader_type::float2 });
		

			m_shader_program = mage::gfx::shader_program::create(
				{
					mage::gfx::vertex_shader::create("res/v.glsl"),
					mage::gfx::fragment_shader::create("res/f.glsl")
				}
			);


			m_camera = mage::gfx::orthographic_camera::create(-1.f, 1.f, -1.f, 1.f, { 0.f, 0.f, 0.f }, 0.f);
		}
		MAGE_DCM(layer);
		~layer()
		{
			MAGE_ERROR("DELETE ORC LAYER");
			delete m_vertex_array;
			delete m_vertex_buffer;
			delete m_index_buffer;
			delete m_shader_program;
			delete m_camera;
		}


		bool on_app_draw(mage::app_draw_event& e) override
		{
			m_shader_program->bind();
			m_shader_program->set_uniform_float3("u_color", m_rect_color);
			m_camera->set_pos(m_camera_pos);
			m_shader_program->set_uniform_mat4("u_view_projection", m_camera->get_view_projection());
			e.get_renderer()->draw(m_index_buffer, m_vertex_array);
			return false;
		}
	private:
		mage::gfx::vertex_array* m_vertex_array;
		mage::gfx::vertex_buffer* m_vertex_buffer;
		mage::gfx::index_buffer* m_index_buffer;
		mage::gfx::shader_program* m_shader_program;
		mage::gfx::orthographic_camera* m_camera;
		glm::vec3 m_rect_color, m_camera_pos;
	};
}
