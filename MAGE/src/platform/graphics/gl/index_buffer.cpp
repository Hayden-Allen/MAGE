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
	index_buffer<USAGE>::index_buffer(size_t count) :
		mage::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::index_buffer>(count)
	{
		MAGE_CORE_TRACE("Create IB {}", this->m_id);
	}
	template<GLenum USAGE>
	index_buffer<USAGE>::index_buffer(s_type* data, size_t count) :
		mage::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::index_buffer>(count)
	{
	mage::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::index_buffer>::write(data, count);
		MAGE_CORE_TRACE("Create IB {}", this->m_id);
	}
}
