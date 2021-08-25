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
	public:
		constexpr static size_t s_invalid = 0, s_placeholder = 1, s_first = 2;
	public:
		MAGE_DCM(bank);
		virtual ~bank()
		{
			for (size_t i = 0; i < COUNT; i++)
				delete m_bank[i];
		}
	public:
		static bool is_valid(HANDLE h)
		{
			return h != s_invalid && h != s_placeholder;
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
			// account for invalid
			return m_next - 1;
		}
		const size_t get_last() const
		{
			return m_next;
		}
	protected:
		size_t m_next;
		T* m_bank[COUNT];
	protected:
		bank() :
			m_next(s_first),
			m_bank{ nullptr }
		{}
	};



	/**
	 * T must also implement the serializable interface
	 */
	template<typename T, typename HANDLE, size_t COUNT>
	class serializable_bank :
		public bank<T, HANDLE, COUNT>,
		public serializable
	{
	public:
		MAGE_DCM(serializable_bank);
	public:
		void save(mage::output_file& out) const final override
		{
			const size_t last = this->get_last();
			out.ulong(last);
			for (size_t i = this->s_first; i < last; i++)
				this->m_bank[i]->save(out);
		}
		void load(mage::input_file& in) final override
		{
			this->m_next = in.ulong();
			for (size_t i = this->s_first; i < this->m_next; i++)
				this->m_bank[i] = new T(in);
		}
	protected:
		serializable_bank() {}
		serializable_bank(input_file& in)
		{
			load(in);
		}
	};
}
