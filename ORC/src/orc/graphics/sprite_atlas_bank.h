#pragma once
#include "pch.h"
#include "sprite_atlas.h"
#include "orc/util/buildable_bank.h"

namespace orc
{
	class sprite_atlas_bank final : public buildable_bank<sprite_atlas, uint16_t, mage::c::sprite_atlas_bank_size>
	{
	public:
		sprite_atlas_bank() {}
		sprite_atlas_bank(coga::input_file& in) :
			buildable_bank<sprite_atlas, uint16_t, mage::c::sprite_atlas_bank_size>(in)
		{}
		COGA_DCM(sprite_atlas_bank);
		~sprite_atlas_bank();
	};
}
