#pragma once
#include "pch.h"

namespace mage
{
	template<typename T>
	class MAGE_API typed
	{
	public:
		MAGE_DCM(typed);
		typedef T s_type;
	protected:
		typed() {}
	};
}
