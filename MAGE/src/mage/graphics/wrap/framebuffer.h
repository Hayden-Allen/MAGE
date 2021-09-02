#pragma once
#include "pch.h"
#include "buffer.h"
#include "shader_program.h"
#include "vertex_array.h"
#include "coga/graphics/framebuffer.h"

namespace mage
{
	typedef COGA_RAN::framebuffer_color_attachment framebuffer_color_attachment;
	typedef COGA_RAN::framebuffer_depth_attachment framebuffer_depth_attachment;



	class framebuffer final : public COGA_RAN::framebuffer
	{
	public:
		framebuffer(coga::event_handler_container& c, s_type w, s_type h, const std::string& vertex, const std::string& fragment, const coga::gfx::shader_preprocessor& p = coga::gfx::shader_preprocessor()) :
			COGA_RAN::framebuffer(c, w, h,
				{
					new mage::framebuffer_color_attachment(w, h),
					new mage::framebuffer_depth_attachment(w, h)
				}
			),
			m_vertex_array(nullptr),
			m_vertex_buffer(nullptr),
			m_index_buffer(nullptr),
			m_shader_program(new shader_program(vertex, fragment, false, p))
		{
			uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
			m_index_buffer = new mage::static_index_buffer(indices, coga::arrlen(indices));
			float vertices[] =
			{
				-1.f, -1.f, 0.f, 0.f,
				 1.f, -1.f,	1.f, 0.f,
				 1.f,  1.f,	1.f, 1.f,
				-1.f,  1.f,	0.f, 1.f
			};
			m_vertex_buffer = new mage::static_vertex_buffer(vertices, coga::arrlen(vertices));
			m_vertex_array = new mage::static_vertex_array(m_vertex_buffer, { coga::gfx::shader_type::float2, coga::gfx::shader_type::float2 });
		}
		COGA_DCM(framebuffer);
		~framebuffer()
		{
			delete m_vertex_array;
			delete m_vertex_buffer;
			delete m_index_buffer;
			delete m_shader_program;
		}
	public:
		void draw() const
		{
			unbind();
			m_shader_program->bind();
			m_attachments[0]->bind(0);
			coga::gfx::renderer::draw(m_index_buffer, m_vertex_array);
		}
		coga::gfx::renderer_id_t const get_color_attachment_id() const
		{
			return m_attachments[0]->get_id();
		}
	private:
		static_vertex_array* m_vertex_array;
		static_vertex_buffer* m_vertex_buffer;
		static_index_buffer* m_index_buffer;
		shader_program* m_shader_program;
	};
}
