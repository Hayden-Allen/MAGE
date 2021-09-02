#pragma once
#include "pch.h"
#include "mage/graphics/sprite.h"

namespace mage
{
	struct tile
	{
		sprite_bank::handle sprite;
		coga::rect<uint8_t> pos;
	};




	template<typename SB>
	static void gen_tile_vertices(const SB& sb, const tile& t, float* const buf, size_t index, const glm::vec2& offset = { 0.f, 0.f })
	{
		// (x, y) offsets
		const float x[mage::c::vertices_per_tile] = 
		{
			1.f * t.pos.min.x,
			1.f * t.pos.max.x,
			1.f * t.pos.max.x,
			1.f * t.pos.min.x
		};
		const float y[mage::c::vertices_per_tile] =
		{
			1.f * t.pos.min.y,
			1.f * t.pos.min.y,
			1.f * t.pos.max.y,
			1.f * t.pos.max.y
		};
		// (s, t) offsets
		mage::sprite_atlas_coords bc = sb.get(t.sprite)->get_base_coords();
		const float tx[mage::c::vertices_per_tile] = { bc.x.get_min(), bc.x.get_max(), bc.x.get_max(), bc.x.get_min() };
		const float ty[mage::c::vertices_per_tile] = { bc.y.get_min(), bc.y.get_min(), bc.y.get_max(), bc.y.get_max() };

		// 4 vertices of (x, y), (s, t), (i) 
		for (size_t i = 0; i < mage::c::vertices_per_tile; i++)
		{
			buf[i * mage::c::floats_per_tile_vertex + 0] = x[i] + offset.x;
			buf[i * mage::c::floats_per_tile_vertex + 1] = y[i] + offset.y;
			buf[i * mage::c::floats_per_tile_vertex + 2] = tx[i];
			buf[i * mage::c::floats_per_tile_vertex + 3] = ty[i];
			buf[i * mage::c::floats_per_tile_vertex + 4] = COGA_CAST(float, index);
		}
	}
}
