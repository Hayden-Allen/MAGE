#pragma once
#include "pch.h"
#include "file.h"

namespace mage
{
	class serializable
	{
	public:
		MAGE_DCM(serializable);
	public:
		virtual void save(output_file& out) const = 0;
		virtual void load(input_file& in) = 0;
	protected:
		serializable() {}
	};
}
