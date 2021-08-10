#include "pch.h"
#include "buffer.h"

namespace mage::gfx
{
#define B(NAME, STATIC, DYNAMIC) \
	NAME* NAME::create_static(NAME::s_type* data, size_t count) { return new mage::gl::STATIC(data, count); } \
	NAME* NAME::create_dynamic(NAME::s_type* data, size_t count) { return new mage::gl::DYNAMIC(data, count); }

	B(index_buffer, static_index_buffer, dynamic_index_buffer);
	B(vertex_buffer, static_vertex_buffer, dynamic_vertex_buffer);

#undef B
}



namespace mage::gl
{
#define B(NAME, TARGET, STRING) \
	template<GLenum USAGE> NAME<USAGE>::NAME(s_type* data, size_t count) : mage::gl::buffer<s_type, TARGET, USAGE>(count), mage::gfx::NAME(count) { write(data, count); MAGE_CORE_TRACE(STRING, m_id); } \
	template<GLenum USAGE> void NAME<USAGE>::write(s_type* data, size_t count) const { mage::gl::buffer<s_type, TARGET, USAGE>::write(data, count); } \
	template<GLenum USAGE> void NAME<USAGE>::bind() const { mage::gl::buffer<s_type, TARGET, USAGE>::bind(); } \
	template<GLenum USAGE> void NAME<USAGE>::unbind() const { mage::gl::buffer<s_type, TARGET, USAGE>::unbind(); } \
	template<GLenum USAGE> void NAME<USAGE>::update(s_type* data, size_t count, size_t offset) const { mage::gl::buffer<s_type, TARGET, USAGE>::update(data, count, offset); }

	B(index_buffer, GL_ELEMENT_ARRAY_BUFFER, "Create IB {}");
	B(vertex_buffer, GL_ARRAY_BUFFER, "Create VB {}");

#undef B
}
