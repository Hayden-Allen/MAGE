#pragma once
#include "pch.h"

namespace mage
{
	template<typename T>
	class MAGE_API positional
	{
	public:
		MAGE_DCM(positional);


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

		positional(T x, T y) :
			m_x(x),
			m_y(y)
		{}
	};
}
