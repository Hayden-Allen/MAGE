#pragma once
#include "pch.h"

namespace mage::gfx
{
	struct shader_preprocessor
	{
	public:
		shader_preprocessor() {}
		MAGE_DCM(shader_preprocessor);
		virtual ~shader_preprocessor() {}


		virtual std::string operator()(std::string& line) const
		{
			return line;
		}
	};
}
