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



	template<typename T>
	class protected_typed
	{
	public:
		MAGE_DCM(protected_typed);
	protected:
		typedef T s_type;
		protected_typed() {}
	};
}
