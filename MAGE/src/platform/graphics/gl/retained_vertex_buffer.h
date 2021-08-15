#pragma once
#include "pch.h"
#include "retained_buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class retained_vertex_buffer : public mage::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::retained_vertex_buffer>
	{
	public:
		MAGE_DM(retained_vertex_buffer);
		virtual ~retained_vertex_buffer()
		{
			MAGE_CORE_TRACE("Delete RVB {}", this->m_id);
		}
	protected:
		retained_vertex_buffer(mage::gfx::retained_vertex_buffer::s_type* data, size_t count) :
			mage::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::retained_vertex_buffer>(data, count)
		{
			MAGE_CORE_TRACE("Create RVB {}", this->m_id);
		}
		retained_vertex_buffer(const retained_vertex_buffer& other, size_t count) :
			mage::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::retained_vertex_buffer>(other, count)
		{
			MAGE_CORE_TRACE("Create RVB {}", this->m_id);
		}
		retained_vertex_buffer(input_file& in) :
			mage::gl::retained_buffer<GL_ARRAY_BUFFER, USAGE, mage::gfx::retained_vertex_buffer>(in)
		{
			MAGE_CORE_TRACE("Create RVB {}", this->m_id);
		}
	};



	class retained_static_vertex_buffer : public mage::gl::retained_vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		retained_static_vertex_buffer(s_type* vertices, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		retained_static_vertex_buffer(const retained_static_vertex_buffer& other, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(other, count)
		{}
		retained_static_vertex_buffer(input_file& in) :
			retained_vertex_buffer<GL_STATIC_DRAW>(in)
		{}
		MAGE_DCM(retained_static_vertex_buffer);
	};



	class retained_dynamic_vertex_buffer : public mage::gl::retained_vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		retained_dynamic_vertex_buffer(s_type* vertices, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		retained_dynamic_vertex_buffer(const retained_dynamic_vertex_buffer& other, size_t count) :
			retained_vertex_buffer<GL_STATIC_DRAW>(other, count)
		{}
		retained_dynamic_vertex_buffer(input_file& in) :
			retained_vertex_buffer<GL_STATIC_DRAW>(in)
		{}
		MAGE_DCM(retained_dynamic_vertex_buffer);
	};
}
