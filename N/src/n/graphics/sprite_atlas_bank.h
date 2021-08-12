#pragma once
#include "pch.h"

namespace n
{
	class sprite_atlas;

	class sprite_atlas_bank final : public mage::serializable_bank<sprite_atlas, uint16_t, c::sprite_atlas_bank_size>
	{
	public:
		sprite_atlas_bank() {}
		sprite_atlas_bank(mage::input_file& in) :
			mage::serializable_bank<sprite_atlas, uint16_t, c::sprite_atlas_bank_size>(in)
		{}
		N_DCM(sprite_atlas_bank);
	};
}
