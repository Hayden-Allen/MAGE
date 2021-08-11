#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	/**
	 * An object with area
	 */
	template<typename T>
	class dimensional : public typed<T>
	{
	public:
		template<typename U = T>
		U get_w() const
		{
			return MAGE_CAST(U, m_w);
		}
		template<typename U = T>
		U get_h() const
		{
			return MAGE_CAST(U, m_h);
		}
	protected:
		T m_w, m_h;


		dimensional(T w, T h) :
			m_w(w),
			m_h(h)
		{}
	};



	/**
	 * An object with volume
	 */
	template<typename T>
	class dimensional3 : public dimensional<T>
	{
	public:
		template<typename U = T>
		U get_d() const
		{
			return MAGE_CAST(U, m_d);
		}
	protected:
		T m_d;


		dimensional3(T w, T h, T d) :
			dimensional<T>(w, h),
			m_d(d)
		{}
	};
}
