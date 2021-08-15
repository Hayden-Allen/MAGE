#pragma once
#include "pch.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	struct tile
	{
		sprite* sprite;
		mage::rect<uint8_t> pos;
	};
}
