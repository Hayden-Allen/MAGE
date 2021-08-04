#pragma once
#include "pch.h"

namespace mage
{
	class MAGE_API application
	{
	public:
		MAGE_DCM(application);


		virtual void run() const = 0;
	protected:
		application() {}
	};


	application* create_application();
}
