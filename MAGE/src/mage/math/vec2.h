#pragma once
#include "pch.h"

namespace mage
{
	template<typename T>
	class MAGE_API vec2
	{
	public:
		MAGE_DCM(vec2);


		T get_x() const
		{
			return m_x;
		}
		T get_y() const
		{
			return m_y;
		}
	protected:
		T m_x, m_y;

		vec2(T x, T y) :
			m_x(x),
			m_y(y)
		{}
	};
}
