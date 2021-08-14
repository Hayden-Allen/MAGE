#pragma once
#include "pch.h"
#include "mage/util/bank.h"

namespace mage::game
{
	class sprite_atlas;

	class sprite_atlas_bank final : public mage::serializable_bank<sprite_atlas, uint16_t, c::sprite_atlas_bank_size>
	{
	public:
		sprite_atlas_bank() {}
		sprite_atlas_bank(input_file& in) :
			serializable_bank<sprite_atlas, uint16_t, c::sprite_atlas_bank_size>(in)
		{}
		MAGE_DCM(sprite_atlas_bank);
	};
}
