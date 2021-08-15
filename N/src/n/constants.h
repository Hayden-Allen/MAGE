#pragma once
#include "pch.h"

namespace n::c
{
	// colors in a sprite's palette
	constexpr static size_t sprite_color_count = 16;
	// pixels per side of a single tile of a sprite
	constexpr static size_t pixels_per_sprite_side = 16;
	// sprites are stored as RGBA
	constexpr static size_t bytes_per_sprite_pixel = 4;
	// sprites can have up to 256 frames
	constexpr static size_t max_sprite_frame_count = 256;


	// allows a max size sprite (256 frames of 256x256 pixels) to fit in a sprite_atlas
	constexpr static size_t sprite_atlas_size = 4096;
	// arbitrary, but should be more than enough for every game, especially since each map has its own banks. Ends up saving a lot of space to serialize Chunk layers using shorts rather than ints or longs.
	constexpr static size_t sprite_bank_size = 65536;
	// this should be WAY more than any game could possibly use, but technically each sprite is allowed to use up to a full atlas (as defined implicitly by sprite_atlas_size), so that case needs to be accounted for.
	constexpr static size_t sprite_atlas_bank_size = 65536;


	// a sampler2D array in GLSL to which textures are bound
	constexpr static char shader_textures[] = "u_textures";
	// a mat4
	constexpr static char shader_camera[] = "u_camera";
	// an array of ints mapping "local" sprite indices (within a sprite_batch) to the index to which the atlas they reference for their current frame is bound
	constexpr static char shader_sprite_to_texture_indices[] = "u_tex_indices";
	// array of vec2s mapping "local" sprite indices (within a sprite_batch) to the difference between the current frames texture coordinates and that sprite's base texture coordinates
	constexpr static char shader_sprite_offsets[] = "u_offsets";


	// each tile is a single sprite (quad)
	constexpr static size_t vertices_per_tile = 4;
	// (x, y), (s, t) (base), (i) (local sprite_batch index)
	constexpr static size_t floats_per_tile_vertex = 5;
	// 0, 1, 2, 0, 2, 3
	constexpr static size_t indices_per_tile = 6;


	// counter-clockwise from bottom left
	constexpr static uint32_t index_buffer_offsets[indices_per_tile] = { 0, 1, 2, 0, 2, 3 };


	// 3 foreground 3 background
	constexpr static size_t layers_per_chunk = 6;
	constexpr static size_t tiles_per_chunk_side = 16;
	constexpr static size_t tiles_per_chunk_layer = tiles_per_chunk_side * tiles_per_chunk_side;
	constexpr static size_t tiles_per_chunk = tiles_per_chunk_layer * layers_per_chunk;
}
