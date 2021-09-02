#pragma once
#include "pch.h"

namespace orc
{
	class sprite_batch;

	class sprite_batch_bank final : public coga::serializable_bank<sprite_batch, uint32_t, c::sprite_batch_bank_size>
	{
	public:
		sprite_batch_bank() {}
		sprite_batch_bank(coga::input_file& in) :
			serializable_bank<sprite_batch, uint32_t, c::sprite_batch_bank_size>(in)
		{}
		COGA_DCM(sprite_batch_bank);
		~sprite_batch_bank();
	};
}
