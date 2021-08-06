#include "pch.h"
#include "vertex_array.h"
#include "vertex_array_description.h"
#include "core.h"

namespace mage::gfx
{
	vertex_array* vertex_array::create_static(mage::gfx::vertex_buffer* const buffer, const mage::gfx::vertex_array_description& desc)
	{
		return new mage::gl::static_vertex_array(MAGE_CAST(mage::gl::static_vertex_buffer*, buffer), MAGE_CAST(const mage::gl::vertex_array_description&, desc));
	}
	vertex_array* vertex_array::create_dynamic(mage::gfx::vertex_buffer* const buffer, const mage::gfx::vertex_array_description& desc)
	{
		return new mage::gl::dynamic_vertex_array(MAGE_CAST(mage::gl::dynamic_vertex_buffer*, buffer), MAGE_CAST(const mage::gl::vertex_array_description&, desc));
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
		mage::gfx::vertex_array(buffer, std::reduce(desc.get_desc().begin(), desc.get_desc().end(), 0, std::plus<s_desc::s_type::value_type>()))
	{
		glGenVertexArrays(1, &this->m_id);

		bind();
		this->m_buffer->bind();

		const uint32_t stride = MAGE_CAST(uint32_t, this->m_vertex_size * sizeof(VBT));
		uint32_t offset = 0, i = 0;
		for (s_desc::s_type::value_type n : desc.get_desc())
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, n, get_type_enum<VBT>(), GL_FALSE, stride, (const void*)(offset * sizeof(VBT)));
			offset += n;
			i++;
		}
		MAGE_CORE_TRACE("Create VA {}", m_id);
	}
#undef VBT
}
