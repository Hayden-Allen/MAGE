#pragma once
#include "pch.h"

namespace n::c
{
	// colors in a sprite's palette
	constexpr static size_t color_count = 16;
	// pixels per side of a tile
	constexpr static size_t pixels_per_side = 16;
	// sprites are stored as RGBA
	constexpr static size_t bytes_per_pixel = 4;
	// sprites can have up to 256 frames
	constexpr static size_t max_frame_count = 256;
	// allows a max size sprite (256 frames of 256x256 pixels) to fit in a sprite_atlas
	constexpr static size_t sprite_atlas_size = 4096;
	// arbitrary, but should be more than enough for every game, especially since each map has its own banks. Ends up saving a lot of space to serialize Chunk layers using shorts rather than ints or longs.
	constexpr static size_t sprite_bank_size = 65536;
	// this should be WAY more than any game could possibly use, but technically each sprite is allowed to use up to a full atlas (as defined implicitly by sprite_atlas_size). Therefore, that case needs to be accounted for.
	constexpr static size_t sprite_atlas_bank_size = 65536;
}
