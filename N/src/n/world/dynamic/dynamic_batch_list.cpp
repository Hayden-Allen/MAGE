#include "pch.h"
#include "dynamic_batch_list.h"
#include "dynamic_batch.h"

namespace n
{
	dynamic_batch_list::~dynamic_batch_list()
	{
		for (size_t i = 0; i < get_next(); i++)
			delete m_list[i];
	}
}
