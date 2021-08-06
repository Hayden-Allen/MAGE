#pragma once
#include "pch.h"
#include "vertex_array_description.h"
#include "vertex_buffer.h"
#include "mage/graphics/vertex_array.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class vertex_array : public mage::gfx::vertex_array
	{
	public:
		typedef mage::gl::vertex_array_description s_desc;


		MAGE_DCM(vertex_array);
		~vertex_array()
		{
			MAGE_CORE_TRACE("Delete VA {}", m_id);
		}

		void bind() const override;
		void unbind() const override;
	protected:
		vertex_array(mage::gl::vertex_buffer<USAGE>* const buffer, const s_desc& desc);
	};



	class static_vertex_array : public mage::gl::vertex_array<GL_STATIC_DRAW>
	{
	public:
		static_vertex_array(mage::gl::static_vertex_buffer* const buffer, const s_desc& desc) :
			mage::gl::vertex_array<GL_STATIC_DRAW>(buffer, desc)
		{}
		MAGE_DCM(static_vertex_array);
	};



	class dynamic_vertex_array : public mage::gl::vertex_array<GL_DYNAMIC_DRAW>
	{
	public:
		dynamic_vertex_array(mage::gl::dynamic_vertex_buffer* const buffer, const s_desc& desc) :
			mage::gl::vertex_array<GL_DYNAMIC_DRAW>(buffer, desc)
		{}
		MAGE_DCM(dynamic_vertex_array);
	};
}
