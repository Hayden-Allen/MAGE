#pragma once
#include "pch.h"
#include "n/graphics/sprite.h"

namespace n
{
	struct tile
	{
		sprite* sprite;
		mage::rect<float> pos;


		constexpr static size_t s_vertices = 4, s_floats_per_vertex = 5, s_indices = 6;
	};
}
