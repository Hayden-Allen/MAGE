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
		script(uint64_t entry_point, const std::vector<uint64_t>& byte_code, const std::vector<hasl::sasm::args>& instructions) :
			hasl::sasm::script<c::script_stack_size, c::script_ram_size>(entry_point, byte_code, instructions)
		{}
		COGA_DCM(script);
	};
}
