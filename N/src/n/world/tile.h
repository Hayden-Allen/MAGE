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



	static void gen_tile_vertices(float* const buf, const tile& t, size_t index)
	{
		// (x, y) offsets
		const float x[n::c::vertices_per_tile] = { t.pos.min.x, t.pos.max.x, t.pos.max.x, t.pos.min.x };
		const float y[n::c::vertices_per_tile] = { t.pos.min.y, t.pos.min.y, t.pos.max.y, t.pos.max.y };
		// (s, t) offsets
		n::sprite_atlas_coords bc = t.sprite->get_base_coords();
		const float tx[n::c::vertices_per_tile] = { bc.x.get_min(), bc.x.get_max(), bc.x.get_max(), bc.x.get_min() };
		const float ty[n::c::vertices_per_tile] = { bc.y.get_min(), bc.y.get_min(), bc.y.get_max(), bc.y.get_max() };

		// 4 vertices of (x, y), (s, t), (i) 
		for (size_t i = 0; i < n::c::vertices_per_tile; i++)
		{
			buf[i * n::c::floats_per_tile_vertex + 0] = x[i];
			buf[i * n::c::floats_per_tile_vertex + 1] = y[i];
			buf[i * n::c::floats_per_tile_vertex + 2] = tx[i];
			buf[i * n::c::floats_per_tile_vertex + 3] = ty[i];
			buf[i * n::c::floats_per_tile_vertex + 4] = MAGE_CAST(float, index);
		}
	}
}
