#pragma once
#include "pch.h"

namespace mage
{
	template<typename T>
	class typed
	{
	public:
		MAGE_DCM(typed);
		typedef T s_type;
	protected:
		typed() {}
	};
}
