#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	template<typename T>
	class iterable : public typed<typename T::value_type>
	{
	public:
		MAGE_DCM(iterable);


		T::iterator begin()
		{
			return m_list.begin();
		}
		T::iterator end()
		{
			return m_list.end();
		}
		T::const_iterator begin() const
		{
			return m_list.begin();
		}
		T::const_iterator end() const
		{
			return m_list.end();
		}
	protected:
		typedef T s_list;
		T m_list;


		iterable() {}
		iterable(const T& list) :
			m_list(list)
		{}
	};
}
