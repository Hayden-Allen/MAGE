#pragma once
#include "pch.h"
#include "sprite_atlas.h"

namespace orc
{
	class sprite_atlas_bank final : public coga::serializable_bank<sprite_atlas, uint16_t, mage::c::sprite_atlas_bank_size>
	{
	public:
		sprite_atlas_bank() {}
		sprite_atlas_bank(coga::input_file& in) :
			serializable_bank<sprite_atlas, uint16_t, mage::c::sprite_atlas_bank_size>(in)
		{}
		COGA_DCM(sprite_atlas_bank);
		~sprite_atlas_bank();
	};
}
