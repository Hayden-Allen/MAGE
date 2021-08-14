#pragma once
#include "pch.h"
#include "sprite_batch_constructor.h"

namespace orc
{
	class sprite_batch final : public n::sprite_batch
	{
	public:
		sprite_batch(const sprite_batch_constructor& constructor);
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) :
			n::sprite_batch(std::move(other))
		{}


		// TODO
		/*void add(const tile& t);
		void remove(const tile& t);*/
	};
}
