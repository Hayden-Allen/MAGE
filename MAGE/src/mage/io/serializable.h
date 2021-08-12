#pragma once
#include "pch.h"
#include "file.h"

namespace mage
{
	class serializable
	{
	public:
		MAGE_DCM(serializable);


		virtual void save(output_file& out) const = 0;
		virtual void load(input_file& in) = 0;
	protected:
		serializable() {}
	};



	class constructable_serializable : public serializable
	{
	public:
		MAGE_DCM(constructable_serializable);
	protected:
		constructable_serializable() {}
		constructable_serializable(input_file& in) {}
	};
}
