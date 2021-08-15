#pragma once
#include "pch.h"
#include "buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class index_buffer : public mage::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::index_buffer>
	{
	protected:
		using s_type = mage::gl::buffer<GL_ELEMENT_ARRAY_BUFFER, USAGE, mage::gfx::index_buffer>::s_type;
	public:
		MAGE_DCM(index_buffer);
		virtual ~index_buffer()
		{
			MAGE_CORE_TRACE("Delete IB {}", this->m_id);
		}
	protected:
		index_buffer(s_type* indices, size_t count);
	};



	class static_index_buffer : public mage::gl::index_buffer<GL_STATIC_DRAW>
	{
	public:
		static_index_buffer(s_type* indices, size_t count) :
			index_buffer<GL_STATIC_DRAW>(indices, count)
		{}
		MAGE_DCM(static_index_buffer);
	};



	class dynamic_index_buffer : public mage::gl::index_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_index_buffer(s_type* indices, size_t count) :
			index_buffer<GL_DYNAMIC_DRAW>(indices, count)
		{}
		MAGE_DCM(dynamic_index_buffer);
	};
}
