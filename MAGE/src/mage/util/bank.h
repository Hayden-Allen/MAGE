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



	/**
	 * T must implement the constructable_serializable interface
	 */
	template<typename T, typename HANDLE, size_t COUNT>
	class serializable_bank :
		public bank<T, HANDLE, COUNT>,
		public constructable_serializable
	{
	public:
		MAGE_DCM(serializable_bank);


		void save(mage::output_file& out) const final override
		{
			const size_t count = this->get_size();
			out.ulong(count);
			for (size_t i = 0; i < count; i++)
				this->m_bank[i]->save(out);
		}
		void load(mage::input_file& in) final override
		{
			this->m_next = in.ulong();
			for (size_t i = 0; i < this->m_next; i++)
				this->m_bank[i] = new T(in);
		}
	protected:
		serializable_bank() {}
		serializable_bank(input_file& in) :
			constructable_serializable(in)
		{
			load(in);
		}
	};
}
