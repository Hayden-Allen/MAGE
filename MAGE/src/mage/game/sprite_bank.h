#pragma once
#include "pch.h"
#include "mage/util/bank.h"

namespace mage::game
{
	class sprite;

	class sprite_bank final : public serializable_bank<sprite, uint16_t, c::sprite_bank_size>
	{
	public:
		sprite_bank() {}
		sprite_bank(input_file& in) :
			serializable_bank<sprite, uint16_t, c::sprite_bank_size>(in)
		{}
		MAGE_DCM(sprite_bank);
	};
}
