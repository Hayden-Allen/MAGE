#pragma once
#include "pch.h"
#include "retained_buffer.h"
#include "vertex_buffer.h"
#include "mage/graphics/vertex_array.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class vertex_array : public mage::gfx::vertex_array
	{
	public:
		MAGE_DCM(vertex_array);
		~vertex_array()
		{
			MAGE_CORE_TRACE("Delete VA {}", m_id);
		}
	public:
		void bind() const override
		{
			glBindVertexArray(this->m_id);
		}
		void unbind() const override
		{
			glBindVertexArray(0);
		}
	protected:
		vertex_array(mage::gl::vertex_buffer<USAGE>* const buffer, const s_desc& desc) :
			mage::gfx::vertex_array(buffer, desc.get_stride())
		{
			init(desc);
		}
		vertex_array(mage::gl::retained_vertex_buffer<USAGE>* const buffer, const s_desc& desc) :
			mage::gfx::vertex_array(buffer, desc.get_stride())
		{
			init(desc);
		}
	private:
		void init(const s_desc& desc)
		{
			glGenVertexArrays(1, &this->m_id);

			bind();
			this->m_buffer->bind();

			uint32_t i = 0;
			for (auto& element : desc)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.get_count<GLint>(), get_shader_type_base(element.get_type()), GL_FALSE, desc.get_stride<GLsizei>(), (const void*)element.get_offset());
				i++;
			}

			MAGE_CORE_TRACE("Create VA {}", m_id);
			unbind();
		}
	};



	class static_vertex_array : public mage::gl::vertex_array<GL_STATIC_DRAW>
	{
	public:
		static_vertex_array(mage::gl::static_vertex_buffer* const buffer, const s_desc& desc) : mage::gl::vertex_array<GL_STATIC_DRAW>(buffer, desc)
		{}
		static_vertex_array(mage::gl::retained_static_vertex_buffer* const buffer, const s_desc & desc) : mage::gl::vertex_array<GL_STATIC_DRAW>(buffer, desc)
		{}
		MAGE_DCM(static_vertex_array);
	};



	class dynamic_vertex_array : public mage::gl::vertex_array<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_array(mage::gl::dynamic_vertex_buffer* const buffer, const s_desc& desc) : mage::gl::vertex_array<GL_DYNAMIC_DRAW>(buffer, desc)
		{}
		dynamic_vertex_array(mage::gl::retained_dynamic_vertex_buffer* const buffer, const s_desc & desc) : mage::gl::vertex_array<GL_DYNAMIC_DRAW>(buffer, desc)
		{}
		MAGE_DCM(dynamic_vertex_array);
	};
}
