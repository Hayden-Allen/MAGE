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
		T get_w() const
		{
			return m_w;
		}
		T get_h() const
		{
			return m_h;
		}
	protected:
		T m_w, m_h;

		dimensional(T w, T h) :
			m_w(w),
			m_h(h)
		{}
	};
}
