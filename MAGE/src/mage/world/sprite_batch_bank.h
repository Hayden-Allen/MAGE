#pragma once
#include "pch.h"

namespace mage
{
	class sprite_batch;

	template<typename T>
	class sprite_batch_bank_base : public
		coga::serializable_bank<T, uint32_t, c::sprite_batch_bank_size>
	{
	public:
		sprite_batch_bank_base() {}
		sprite_batch_bank_base(coga::input_file& in) :
			coga::serializable_bank<T, uint32_t, c::sprite_batch_bank_size>(in)
		{}
		COGA_DCM(sprite_batch_bank_base);
	};

	class sprite_batch_bank final : public sprite_batch_bank_base<sprite_batch>
	{
	public:
		sprite_batch_bank(coga::input_file& in) :
			sprite_batch_bank_base<sprite_batch>(in)
		{}
		COGA_DCM(sprite_batch_bank);
		~sprite_batch_bank();
	};
}
