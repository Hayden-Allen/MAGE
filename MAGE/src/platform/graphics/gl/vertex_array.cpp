#include "pch.h"
#include "shader_type.h"
#include "vertex_array.h"

namespace mage::gfx
{
	vertex_array* vertex_array::create_static(mage::gfx::vertex_buffer* const buffer, const mage::gfx::vertex_array_description& desc)
	{
		return new mage::gl::static_vertex_array(MAGE_CAST(mage::gl::static_vertex_buffer*, buffer), desc);
	}
	vertex_array* vertex_array::create_dynamic(mage::gfx::vertex_buffer* const buffer, const mage::gfx::vertex_array_description& desc)
	{
		return new mage::gl::dynamic_vertex_array(MAGE_CAST(mage::gl::dynamic_vertex_buffer*, buffer), desc);
	}
}



namespace mage::gl
{
	template<GLenum USAGE>
	void vertex_array<USAGE>::bind() const
	{
		glBindVertexArray(this->m_id);
	}
	template<GLenum USAGE>
	void vertex_array<USAGE>::unbind() const
	{
		glBindVertexArray(0);
	}


#define VBT mage::gl::vertex_buffer<USAGE>::s_type
	template<GLenum USAGE>
	vertex_array<USAGE>::vertex_array(mage::gl::vertex_buffer<USAGE>* const buffer, const s_desc& desc) :
		mage::gfx::vertex_array(buffer, desc.get_stride())
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
	}
#undef VBT
}
