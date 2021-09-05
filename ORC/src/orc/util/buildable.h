#pragma once
#include "pch.h"

namespace orc
{
	class buildable
	{
	public:
		COGA_DCM(buildable);
	public:
		virtual void build(coga::output_file& out) const = 0;
	protected:
		buildable() {}
	};
}
