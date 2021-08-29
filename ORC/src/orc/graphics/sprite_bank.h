#pragma once
#include "pch.h"
#include "sprite.h"

namespace orc
{
	class sprite_bank final : public mage::serializable_bank<sprite, uint16_t, n::c::sprite_bank_size>
	{
	public:
		sprite_bank() {}
		sprite_bank(mage::input_file& in) :
			serializable_bank<sprite, uint16_t, n::c::sprite_bank_size>(in)
		{}
		MAGE_DCM(sprite_bank);
		~sprite_bank();
	};
}
