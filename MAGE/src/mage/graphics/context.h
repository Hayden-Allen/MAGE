#pragma once
#include "pch.h"

namespace mage::gfx
{
	class context
	{
	public:
		MAGE_DCM(context);
		virtual void init() = 0;
		virtual void clear_screen() = 0;
		virtual void swap_buffers() = 0;
	protected:
		context() {}
	};
}
