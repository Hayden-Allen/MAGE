#pragma once
#include "pch.h"
#include "n/graphics/sprite.h"

namespace n
{
	struct tile
	{
		n::sprite* sprite;
		mage::rect<float> pos;
	};
}
