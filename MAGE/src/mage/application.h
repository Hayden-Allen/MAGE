#pragma once
#include "core.h"

namespace mage
{
	class MAGE_API application
	{
	public:
		MAGE_DCM(application);
		virtual ~application();


		virtual void run() const;
	protected:
		application();
	};


	application* create_application();
}
