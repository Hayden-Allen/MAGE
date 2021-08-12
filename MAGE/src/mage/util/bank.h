#pragma once
#include "pch.h"
#include "typed.h"

namespace mage
{
	template<typename T, typename HANDLE, size_t COUNT>
	class bank : public typed<T>
	{
	public:
		typedef HANDLE handle;


		MAGE_DCM(bank);
		virtual ~bank()
		{
			for (size_t i = 0; i < COUNT; i++)
				delete m_bank[i];
		}


		handle add(T* t)
		{
			MAGE_CORE_ASSERT(m_next < COUNT, "Bank is full ({}/{})", COUNT, COUNT);
			handle ret = MAGE_CAST(handle, m_next);
			m_bank[m_next++] = t;
			return ret;
		}
		T* const get(HANDLE h)
		{
			return m_bank[MAGE_CAST(size_t, h)];
		}
		const T* const get(HANDLE h) const
		{
			return m_bank[MAGE_CAST(size_t, h)];
		}
		const size_t get_size() const
		{
			return m_next;
		}
	protected:
		size_t m_next;
		T* m_bank[COUNT];


		bank() :
			m_next(0),
			m_bank{ nullptr }
		{}
	};
}
