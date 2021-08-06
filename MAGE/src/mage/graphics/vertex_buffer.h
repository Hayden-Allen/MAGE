#pragma once
#include "pch.h"
#include "buffer.h"

namespace mage::gfx
{
	class vertex_buffer : public buffer<float>
	{
	public:
		virtual ~vertex_buffer() {}


		static vertex_buffer* create_static(s_type* vertices, size_t count);
		static vertex_buffer* create_dynamic(s_type* vertices, size_t count);
	protected:
		vertex_buffer(size_t count) :
			buffer<s_type>(count)
		{}
	};
}
