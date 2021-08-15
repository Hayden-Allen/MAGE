#include "pch.h"
#include "vertex_buffer.h"

namespace mage::gfx
{
	vertex_buffer* vertex_buffer::create_static(vertex_buffer::s_type* data, size_t count)
	{
		return new mage::gl::static_vertex_buffer(data, count);
	}
	vertex_buffer* vertex_buffer::create_dynamic(vertex_buffer::s_type* data, size_t count)
	{
		return new mage::gl::dynamic_vertex_buffer(data, count);
	}
}


namespace mage::gl
{
	template<GLenum USAGE>
	vertex_buffer<USAGE>::vertex_buffer(s_type* data, size_t count) :
		mage::gl::buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::vertex_buffer>(count)
	{
		mage::gl::buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::vertex_buffer>::write(data, count);
		MAGE_CORE_TRACE("Create VB {}", this->m_id);
	}
}
