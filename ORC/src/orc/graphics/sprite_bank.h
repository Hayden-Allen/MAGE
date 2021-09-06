#pragma once
#include "pch.h"
#include "sprite.h"
#include "orc/util/buildable_bank.h"

namespace orc
{
	class sprite_bank final :
		public buildable_bank<sprite, uint16_t, mage::c::sprite_bank_size>
	{
	public:
		sprite_bank() {}
		sprite_bank(coga::input_file& in) :
			buildable_bank<sprite, uint16_t, mage::c::sprite_bank_size>(in)
		{}
		COGA_DCM(sprite_bank);
		~sprite_bank();
	};
}
