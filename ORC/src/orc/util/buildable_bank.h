#pragma once
#include "pch.h"
#include "buildable.h"

namespace orc
{
	template<typename T, typename HANDLE, size_t COUNT>
	class buildable_bank :
		public coga::serializable_bank<T, HANDLE, COUNT>,
		public buildable
	{
	public:
		buildable_bank() {}
		buildable_bank(coga::input_file& in) :
			coga::serializable_bank<T, HANDLE, COUNT>(in)
		{}
		COGA_DCM(buildable_bank);
	public:
		void build(coga::output_file& out) const final override
		{
			const size_t last = this->get_last();
			out.ulong(last);
			for (size_t i = this->s_first; i < last; i++)
				this->m_bank[i]->build(out);
		}
	};
}
