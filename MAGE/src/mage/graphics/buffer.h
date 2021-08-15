#pragma once
#include "pch.h"
#include "render_object.h"
#include "mage/io/serializable.h"
#include "mage/util/functions.h"
#include "mage/util/typed.h"

namespace mage::gfx
{
	template<typename T>
	class buffer :
		public render_object,
		public typed<T>
	{
	public:
		MAGE_DCM(buffer);


		virtual void update(T* data, size_t count, size_t offset) const = 0;
		template<typename T = size_t>
		T get_count() const
		{
			return MAGE_CAST(T, m_count);
		}
	protected:
		size_t m_count;


		buffer(size_t count) :
			m_count(count)
		{}


		virtual void write(T* data, size_t count) const = 0;
	};



#define B(NAME, TYPE) \
	class NAME : public buffer<TYPE> { \
	public: \
		virtual ~NAME() {} \
		static NAME* create_static(s_type* vertices, size_t count); \
		static NAME* create_dynamic(s_type* vertices, size_t count); \
	protected: \
		NAME(size_t count) : buffer<TYPE>(count) {}	};

	B(index_buffer, uint32_t);
	B(vertex_buffer, float);
	
#undef B

#define B(NAME, BASE, TYPE) \
	class NAME : public BASE, public serializable { \
	public: \
		virtual ~NAME() { delete m_data; } \
		static NAME* create_static(s_type* vertices, size_t count); \
		static NAME* create_dynamic(s_type* vertices, size_t count); \
		virtual void save(output_file& out) const override { out.ulong(m_count); out.write(m_data, m_count); } \
		virtual void load(input_file& in) override { m_count = in.ulong(); m_data = new TYPE[m_count]; in.read(m_data, m_count); } \
	protected: \
		TYPE* m_data; \
		NAME(s_type* const data, size_t count) : BASE(count), m_data(data) {} \
		NAME(const NAME& other, size_t count) : BASE(count), m_data(new TYPE[count]) { arrcopy(other.get_count(), other.m_data, m_data); arrset(count - other.get_count(), m_data, MAGE_CAST(TYPE, 0), other.get_count()); } \
		NAME(size_t count) : BASE(count), m_data(new TYPE[count]) {} }

	B(retained_index_buffer, index_buffer, uint32_t);
	B(retained_vertex_buffer, vertex_buffer, float);

#undef B
}
