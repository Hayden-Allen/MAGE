#pragma once
#include "pch.h"

namespace n
{
	class dynamic_batch;

	class dynamic_batch_list : public mage::indexed_list<dynamic_batch*, size_t, dynamic_batch* const, size_t>
	{
	public:
		dynamic_batch_list(size_t count) : 
			mage::indexed_list<dynamic_batch*, size_t, dynamic_batch* const, size_t>(count, nullptr)
		{}
		N_DCM(dynamic_batch_list);
		~dynamic_batch_list();
	public:
		size_t add(dynamic_batch* const batch) override
		{
			return add_base(batch);
		}
		void remove(size_t i) override
		{
			remove_base(i);
		}
	};
}
