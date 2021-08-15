#pragma once
#include "pch.h"
#include "vertex_buffer.h"
#include "mage/graphics/vertex_array.h"

namespace mage::gl
{
	template<GLenum USAGE>
	class vertex_array : public mage::gfx::vertex_array
	{
	public:
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



#define V(NAME, BUFFER, USAGE) \
	class NAME : public mage::gl::vertex_array<USAGE> { \
	public: \
		NAME(mage::gl::BUFFER* const buffer, const s_desc& desc) : mage::gl::vertex_array<USAGE>(buffer, desc) {} \
		MAGE_DCM(NAME);	};

	V(static_vertex_array, static_vertex_buffer, GL_STATIC_DRAW);
	V(dynamic_vertex_array, dynamic_vertex_buffer, GL_DYNAMIC_DRAW);

#undef V
}
