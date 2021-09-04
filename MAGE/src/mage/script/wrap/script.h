#pragma once
#include "pch.h"

namespace mage::sasm
{
	class script final : public hasl::sasm::script<c::script_stack_size, c::script_ram_size>
	{
	public:
		script(const char* fp, hasl::sasm::vm<c::script_stack_size, c::script_ram_size>* const vm) :
			hasl::sasm::script<c::script_stack_size, c::script_ram_size>(fp, vm)
		{}
		COGA_DCM(script);
	};
}
