#pragma once
#include "pch.h"
#include "render_object.h"
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
}
