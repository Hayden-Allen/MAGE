#pragma once
#include "pch.h"

namespace n
{
	class sprite_atlas;

	class sprite_atlas_bank final : public mage::bank<sprite_atlas, uint8_t, 256>
	{};
}
