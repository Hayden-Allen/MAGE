#pragma once
#include "pch.h"
#include "buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class vertex_buffer : public mage::gl::buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::vertex_buffer>
	{
	protected:
		using s_type = mage::gl::buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::vertex_buffer>::s_type;
	public:
		MAGE_DCM(vertex_buffer);
		virtual ~vertex_buffer()
		{
			MAGE_CORE_TRACE("Delete VB {}", this->m_id);
		}
	protected:
		vertex_buffer(s_type* vertices, size_t count);
	};



	class static_vertex_buffer : public mage::gl::vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		static_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		MAGE_DCM(static_vertex_buffer);
	};



	class dynamic_vertex_buffer : public mage::gl::vertex_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_DYNAMIC_DRAW>(vertices, count)
		{}
		MAGE_DCM(dynamic_vertex_buffer);
	};
}
