#pragma once
#include "pch.h"
#include "buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class index_buffer :
		public mage::gl::buffer<mage::gfx::index_buffer::s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>,
		public mage::gfx::index_buffer
	{
		// both parent classes are render_objects, but this is the one that actually gets assigned to
		using mage::gl::buffer<mage::gfx::index_buffer::s_type, GL_ELEMENT_ARRAY_BUFFER, USAGE>::m_id;
	public:
		MAGE_DCM(index_buffer);
		~index_buffer()
		{
			MAGE_CORE_TRACE("Delete IB {}", m_id);
		}


		void bind() const override;
		void unbind() const override;
		void update(s_type* data, size_t count, size_t offset) const override;
	protected:
		index_buffer(s_type* indices, size_t count);


		void write(s_type* data, size_t count) const override;
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
