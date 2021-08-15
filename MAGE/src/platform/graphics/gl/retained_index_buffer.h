#pragma once
#include "pch.h"
#include "retained_buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class retained_index_buffer : public mage::gl::retained_buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::retained_index_buffer>
	{
	public:
		MAGE_DM(retained_index_buffer);
		virtual ~retained_index_buffer()
		{
			MAGE_CORE_TRACE("Delete IB {}", this->m_id);
		}
	protected:
		retained_index_buffer(mage::gfx::retained_index_buffer::s_type* data, size_t count) :
			mage::gl::retained_buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::retained_index_buffer>(data, count)
		{
			MAGE_CORE_TRACE("Create IB {}", this->m_id);
		}
		retained_index_buffer(const retained_index_buffer& other, size_t count) :
			mage::gl::retained_buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::retained_index_buffer>(other, count)
		{
			MAGE_CORE_TRACE("Create IB {}", this->m_id);
		}
		retained_index_buffer(input_file& in) :
			mage::gl::retained_buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::retained_index_buffer>(in)
		{
			MAGE_CORE_TRACE("Create IB {}", this->m_id);
		}
	};



	class retained_static_index_buffer : public mage::gl::retained_index_buffer<GL_STATIC_DRAW>
	{
	public:
		retained_static_index_buffer(s_type* indices, size_t count) :
			retained_index_buffer<GL_STATIC_DRAW>(indices, count)
		{}
		retained_static_index_buffer(const retained_static_index_buffer& other, size_t count) :
			retained_index_buffer<GL_STATIC_DRAW>(other, count)
		{}
		retained_static_index_buffer(input_file& in) :
			retained_index_buffer<GL_STATIC_DRAW>(in)
		{}
		MAGE_DCM(retained_static_index_buffer);
	};



	class retained_dynamic_index_buffer : public mage::gl::retained_index_buffer<GL_STATIC_DRAW>
	{
	public:
		retained_dynamic_index_buffer(s_type* indices, size_t count) :
			retained_index_buffer<GL_STATIC_DRAW>(indices, count)
		{}
		retained_dynamic_index_buffer(const retained_dynamic_index_buffer& other, size_t count) :
			retained_index_buffer<GL_STATIC_DRAW>(other, count)
		{}
		retained_dynamic_index_buffer(input_file& in) :
			retained_index_buffer<GL_STATIC_DRAW>(in)
		{}
		MAGE_DCM(retained_dynamic_index_buffer);
	};
}
