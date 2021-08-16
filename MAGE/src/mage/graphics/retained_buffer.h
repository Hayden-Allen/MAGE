#pragma once
#include "pch.h"
#include "buffer.h"
#include "mage/io/serializable.h"
#include "mage/util/functions.h"

namespace mage::gfx
{
	template<typename T>
	class retained_buffer : public serializable
	{
	public:
		virtual ~retained_buffer()
		{
			delete m_data;
		}
	protected:
		T* m_data;
	protected:
		retained_buffer(T* const data) :
			m_data(data)
		{}
	};



	class retained_index_buffer :
		public retained_buffer<index_buffer::s_type>,
		public index_buffer
	{
	public:
		virtual void save(output_file& out) const override
		{
			out.ulong(m_count);
			out.write(m_data, m_count);
		}
		virtual void load(input_file& in) override
		{
			m_count = in.ulong();
			m_data = new s_type[m_count];
			in.read(m_data, m_count);
		}
	protected:
		retained_index_buffer(size_t count) :
			retained_buffer<s_type>(new s_type[count]),
			index_buffer(count)
		{}
		retained_index_buffer(s_type* const data, size_t count) :
			retained_buffer<s_type>(data),
			index_buffer(count)
		{}
		retained_index_buffer(const retained_index_buffer& other, size_t count) :
			retained_buffer<s_type>(new s_type[count]),
			index_buffer(count)
		{
			arrcopy(other.get_count(), other.m_data, m_data);
			arrset(count - other.get_count(), m_data, MAGE_CAST(s_type, 0), other.get_count());
		}
	};



	class retained_vertex_buffer :
		public retained_buffer<vertex_buffer::s_type>,
		public vertex_buffer
	{
	public:
		virtual void save(output_file& out) const override
		{
			out.ulong(m_count);
			out.write(m_data, m_count);
		}
		virtual void load(input_file& in) override
		{
			m_count = in.ulong();
			m_data = new s_type[m_count];
			in.read(m_data, m_count);
		}
	protected:
		retained_vertex_buffer(size_t count) :
			retained_buffer<s_type>(new s_type[count]),
			vertex_buffer(count)
		{}
		retained_vertex_buffer(s_type* const data, size_t count) :
			retained_buffer<s_type>(data),
			vertex_buffer(count)
		{}
		retained_vertex_buffer(const retained_vertex_buffer& other, size_t count) :
			retained_buffer<s_type>(new s_type[count]),
			vertex_buffer(count)
		{
			arrcopy(other.get_count(), other.m_data, m_data);
			arrset(count - other.get_count(), m_data, MAGE_CAST(s_type, 0), other.get_count());
		}
	};
}