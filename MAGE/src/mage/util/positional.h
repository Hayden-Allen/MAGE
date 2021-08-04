#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	/**
	 * An object with position
	 */
	template<typename T>
	class MAGE_API positional : public typed<T>
	{
	public:
		template<typename U = T>
		U get_x() const
		{
			return MAGE_CAST(U, m_x);
		}
		template<typename U = T>
		U get_y() const
		{
			return MAGE_CAST(U, m_y);
		}
	protected:
		T m_x, m_y;

		positional(T x, T y) :
			m_x(x),
			m_y(y)
		{}
	};
}
