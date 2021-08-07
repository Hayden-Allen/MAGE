#pragma once
#include "pch.h"
#include "buffer.h"
#include "render_object.h"
#include "vertex_array_description.h"
#include "mage/util/typed.h"

namespace mage::gfx
{
	class vertex_array :
		public render_object,
		public typed<vertex_buffer::s_type>
	{
	public:
		MAGE_DCM(vertex_array);
		virtual ~vertex_array() {}

		static vertex_array* create_static(vertex_buffer* const buffer, const vertex_array_description& desc);
		static vertex_array* create_dynamic(vertex_buffer* const buffer, const vertex_array_description& desc);
		size_t get_vertex_count() const
		{
			return m_buffer->get_count() / m_vertex_size;
		}
		const vertex_buffer& get_buffer() const
		{
			return *m_buffer;
		}
	protected:
		typedef vertex_array_description s_desc;


		vertex_buffer* m_buffer;
		size_t m_vertex_size;


		vertex_array(vertex_buffer* const buffer, size_t vertex_size) :
			m_buffer(buffer),
			m_vertex_size(vertex_size)
		{}
	};
}
