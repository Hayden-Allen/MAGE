#pragma once
#include "pch.h"

namespace mage
{
	class sprite;

	class sprite_bank final : public coga::serializable_bank<sprite, uint16_t, c::sprite_bank_size>
	{
	public:
		sprite_bank() {}
		sprite_bank(coga::input_file& in) :
			serializable_bank<sprite, uint16_t, c::sprite_bank_size>(in)
		{}
		COGA_DCM(sprite_bank);
		~sprite_bank();
	};
}
