#pragma once
#include "pch.h"

namespace n
{
	class sprite;

	class sprite_bank final : public mage::serializable_bank<sprite, uint16_t, c::sprite_bank_size>
	{
	public:
		sprite_bank() {}
		sprite_bank(mage::input_file& in) :
			mage::serializable_bank<sprite, uint16_t, c::sprite_bank_size>(in)
		{}
		N_DCM(sprite_bank);
	};
}
