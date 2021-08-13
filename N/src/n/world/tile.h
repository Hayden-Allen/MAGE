#pragma once
#include "pch.h"
#include "n/graphics/sprite.h"

namespace n
{
	struct tile
	{
		sprite* sprite;
		mage::rect<float> pos;
	};
}
