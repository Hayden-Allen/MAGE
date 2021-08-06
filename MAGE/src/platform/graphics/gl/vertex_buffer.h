#pragma once
#include "pch.h"
#include "buffer.h"
#include "mage/graphics/vertex_buffer.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class vertex_buffer :
		public mage::gl::buffer<mage::gfx::vertex_buffer::s_type, GL_ARRAY_BUFFER, USAGE>,
		public mage::gfx::vertex_buffer
	{
		// both parent classes are render_objects, but this is the one that actually gets assigned to
		using mage::gl::buffer<mage::gfx::vertex_buffer::s_type, GL_ARRAY_BUFFER, USAGE>::m_id;
	public:
		MAGE_DCM(vertex_buffer);
		~vertex_buffer()
		{
			MAGE_CORE_TRACE("Delete VB {}", m_id);
		}

		void bind() const override;
		void unbind() const override;
		void update(s_type* data, size_t count, size_t offset) const override;
	protected:
		vertex_buffer(s_type* vertices, size_t count);


		void write(s_type* data, size_t count) const override;
	};



	class static_vertex_buffer final : public mage::gl::vertex_buffer<GL_STATIC_DRAW>
	{
	public:
		static_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_STATIC_DRAW>(vertices, count)
		{}
		MAGE_DCM(static_vertex_buffer);
	};



	class dynamic_vertex_buffer final : public mage::gl::vertex_buffer<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_buffer(s_type* vertices, size_t count) :
			vertex_buffer<GL_DYNAMIC_DRAW>(vertices, count)
		{}
		MAGE_DCM(dynamic_vertex_buffer);
	};
}
