#pragma once
#include "pch.h"
#include "n/graphics/sprite.h"

namespace n
{
	struct tile
	{
		sprite_bank::handle sprite;
		mage::rect<uint8_t> pos;
	};




	template<typename SB>
	static void gen_tile_vertices(const SB& sb, const tile& t, float* const buf, size_t index, const glm::vec2& offset = { 0.f, 0.f })
	{
		// (x, y) offsets
		const float x[n::c::vertices_per_tile] = 
		{
			1.f * t.pos.min.x,
			1.f * t.pos.max.x,
			1.f * t.pos.max.x,
			1.f * t.pos.min.x
		};
		const float y[n::c::vertices_per_tile] =
		{
			1.f * t.pos.min.y,
			1.f * t.pos.min.y,
			1.f * t.pos.max.y,
			1.f * t.pos.max.y
		};
		// (s, t) offsets
		n::sprite_atlas_coords bc = sb.get(t.sprite)->get_base_coords();
		const float tx[n::c::vertices_per_tile] = { bc.x.get_min(), bc.x.get_max(), bc.x.get_max(), bc.x.get_min() };
		const float ty[n::c::vertices_per_tile] = { bc.y.get_min(), bc.y.get_min(), bc.y.get_max(), bc.y.get_max() };

		// 4 vertices of (x, y), (s, t), (i) 
		for (size_t i = 0; i < n::c::vertices_per_tile; i++)
		{
			buf[i * n::c::floats_per_tile_vertex + 0] = x[i] + offset.x;
			buf[i * n::c::floats_per_tile_vertex + 1] = y[i] + offset.y;
			buf[i * n::c::floats_per_tile_vertex + 2] = tx[i];
			buf[i * n::c::floats_per_tile_vertex + 3] = ty[i];
			buf[i * n::c::floats_per_tile_vertex + 4] = MAGE_CAST(float, index);
		}
	}
}
