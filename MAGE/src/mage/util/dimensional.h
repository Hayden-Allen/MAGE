#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	/**
	 * An object with area
	 */
	template<typename T>
	class MAGE_API dimensional : public typed<T>
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
}
