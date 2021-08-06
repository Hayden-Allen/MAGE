#pragma once
#include "pch.h"

namespace mage::gfx
{
	class context
	{
	public:
		MAGE_DCM(context);
		virtual void init() = 0;
	protected:
		context() {}
	};
}
