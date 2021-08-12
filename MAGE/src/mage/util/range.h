#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	struct range_contains
	{
		bool left = false, right = false;
	};
	struct range_overlaps
	{
		range_contains min = {}, max = {};
	};



	template<typename T>
	class range : public typed<T>
	{
	public:
		range(const T& min, const T& max) :
			m_min(min),
			m_max(max)
		{
			MAGE_CORE_ASSERT(min < max, "Range min ({}) must be < than max ({})", min, max);
		}


		void operator=(const range<T>& other)
		{
			m_min = other.m_min;
			m_max = other.m_max;
		}
		template<typename U = T>
		bool operator==(const range<U>& other) const
		{
			return m_min == MAGE_CAST(T, other.m_min) && m_max == MAGE_CAST(T, other.m_max);
		}
		template<typename U = T>
		bool contains(const U& value, const range_contains& params = {}) const
		{
			return (params.left ? m_min <= value : m_min < value) && (params.right ? m_max >= value : m_max > value);
		}
		template<typename U = T>
		bool contains(const range<U>& other, const range_overlaps& params = {}) const
		{
			return contains(other.m_min, params.min) && contains(other.m_max, params.max);
		}
		template<typename U = T>
		bool overlaps(const range<U>& other, const range_overlaps& params = {}) const
		{
			return contains(other.m_min, params.min) || contains(other.m_max, params.max);
		}
		template<typename U = T, typename R = T>
		U map(const U& value, const range<R>& other) const
		{
			return MAGE_CAST(U, value / get_span<U>() * other.get_span<U>());
		}
		template<typename U = T>
		U get_min() const
		{
			return MAGE_CAST(U, m_min);
		}
		template<typename U = T>
		U get_max() const
		{
			return MAGE_CAST(U, m_max);
		}
		template<typename U = T>
		U get_span() const
		{
			return MAGE_CAST(U, m_max - m_min);
		}
	private:
		T m_min, m_max;
	};
}
