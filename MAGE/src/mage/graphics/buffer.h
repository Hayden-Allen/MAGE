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
		size_t get_count() const
		{
			return m_count;
		}
	protected:
		size_t m_count;


		buffer(size_t count) :
			m_count(count)
		{}


		virtual void write(T* data, size_t count) const = 0;
	};
}
