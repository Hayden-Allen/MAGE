#pragma once
#include "pch.h"
#include "sprite_atlas.h"

namespace orc
{
	class sprite_atlas_bank final : public mage::serializable_bank<sprite_atlas, uint16_t, n::c::sprite_atlas_bank_size>
	{
	public:
		sprite_atlas_bank() {}
		sprite_atlas_bank(mage::input_file& in) :
			serializable_bank<sprite_atlas, uint16_t, n::c::sprite_atlas_bank_size>(in)
		{}
		MAGE_DCM(sprite_atlas_bank);
	};
}
