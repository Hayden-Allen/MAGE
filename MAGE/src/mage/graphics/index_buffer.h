#pragma once
#include "pch.h"
#include "buffer.h"

namespace mage::gfx
{
	class index_buffer : public buffer<uint32_t>
	{
	public:
		virtual ~index_buffer() {}


		static index_buffer* create_static(s_type* indices, size_t count);
		static index_buffer* create_dynamic(s_type* indices, size_t count);
	protected:
		index_buffer(size_t count) :
			buffer<s_type>(count)
		{}
	};
}
