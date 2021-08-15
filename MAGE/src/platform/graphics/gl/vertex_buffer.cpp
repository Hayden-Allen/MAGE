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
		mage::gl::buffer<s_type, GL_ARRAY_BUFFER, USAGE>(count),
		mage::gfx::vertex_buffer(count)
	{
		write(data, count);
		MAGE_CORE_TRACE("Create IB {}", m_id);
	}
	template<GLenum USAGE>
	void vertex_buffer<USAGE>::bind() const
	{
		mage::gl::buffer<s_type, GL_ARRAY_BUFFER, USAGE>::bind();
	}
	template<GLenum USAGE>
	void vertex_buffer<USAGE>::unbind() const
	{
		mage::gl::buffer<s_type, GL_ARRAY_BUFFER, USAGE>::unbind();
	}
	template<GLenum USAGE>
	void vertex_buffer<USAGE>::update(s_type* data, size_t count, size_t offset) const
	{
		mage::gl::buffer<s_type, GL_ARRAY_BUFFER, USAGE>::update(data, count, offset);
	}
	template<GLenum USAGE>
	void vertex_buffer<USAGE>::write(s_type* data, size_t count) const
	{
		mage::gl::buffer<s_type, GL_ARRAY_BUFFER, USAGE>::write(data, count);
	}
}
