#pragma once
#include "pch.h"

namespace n::c
{
	constexpr static size_t color_count = 16, pixels_per_side = 16, bytes_per_pixel = 4, max_frame_count = 256;
	// allows a max size sprite (256 frames of 256x256 pixels) to fit
	constexpr static size_t sprite_atlas_size = 4096, sprite_atlas_bank_size = 256, sprite_bank_size = 65536;
}
