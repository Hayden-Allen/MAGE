#pragma once
#include "pch.h"

namespace mage
{
	class dynamic_batch;

	class dynamic_batch_list : public coga::indexed_list<dynamic_batch*, size_t, dynamic_batch* const, size_t>
	{
	public:
		dynamic_batch_list(size_t count) : 
			coga::indexed_list<dynamic_batch*, size_t, dynamic_batch* const, size_t>(count, nullptr)
		{}
		COGA_DCM(dynamic_batch_list);
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
