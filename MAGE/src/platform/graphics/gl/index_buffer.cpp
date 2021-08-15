#include "pch.h"
#include "index_buffer.h"

namespace mage::gfx
{
	index_buffer* index_buffer::create_static(index_buffer::s_type* data, size_t count)
	{
		return new mage::gl::static_index_buffer(data, count);
	}
	index_buffer* index_buffer::create_dynamic(index_buffer::s_type* data, size_t count)
	{
		return new mage::gl::dynamic_index_buffer(data, count);
	}
}


namespace mage::gl
{
	template<GLenum USAGE>
	index_buffer<USAGE>::index_buffer(s_type* data, size_t count) :
		mage::gl::buffer<s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>(count),
		mage::gfx::index_buffer(count)
	{
		write(data, count);
		MAGE_CORE_TRACE("Create IB {}", m_id);
	}
	template<GLenum USAGE> 
	void index_buffer<USAGE>::bind() const
	{
		mage::gl::buffer<s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>::bind();
	}
	template<GLenum USAGE>
	void index_buffer<USAGE>::unbind() const
	{
		mage::gl::buffer<s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>::unbind();
	}
	template<GLenum USAGE>
	void index_buffer<USAGE>::update(s_type* data, size_t count, size_t offset) const
	{
		mage::gl::buffer<s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>::update(data, count, offset);
	}
	template<GLenum USAGE>
	void index_buffer<USAGE>::write(s_type* data, size_t count) const
	{
		mage::gl::buffer<s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>::write(data, count);
	}
}
