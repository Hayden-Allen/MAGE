#pragma once
#include "pch.h"

namespace orc
{
	class sprite_batch;

	class sprite_batch_bank final : public mage::sprite_batch_bank_base<sprite_batch>
	{
	public:
		sprite_batch_bank() {}
		sprite_batch_bank(coga::input_file& in) :
			sprite_batch_bank_base<sprite_batch>(in)
		{}
		COGA_DCM(sprite_batch_bank);
		~sprite_batch_bank();
	};
}
