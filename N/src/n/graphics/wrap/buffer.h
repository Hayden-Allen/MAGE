#pragma once
#include "pch.h"

namespace n
{
	static uint32_t* gen_indices(size_t tiles)
	{
		const size_t count = tiles * mage::game::c::indices_per_tile;
		uint32_t* indices = new uint32_t[count];
		// use base pattern [0, 1, 2, 0, 2, 3] but increment by 4 for each successive tile
		for (size_t i = 0; i < count; i++)
			indices[i] = MAGE_CAST(uint32_t, i / mage::game::c::indices_per_tile * mage::game::c::vertices_per_tile + mage::game::c::index_buffer_offsets[i % mage::game::c::indices_per_tile]);

		return indices;
	}



	N_WRAP
	(
		static_index_buffer,
		static_index_buffer,
		(s_type* indices, size_t tiles),
		(indices, tiles * mage::game::c::indices_per_tile)
	);

	N_WRAP
	(
		dynamic_index_buffer,
		dynamic_index_buffer,
		(s_type* indices, size_t tiles),
		(indices, tiles* mage::game::c::indices_per_tile)
	);



	N_WRAP
	(
		static_vertex_buffer,
		static_vertex_buffer,
		(s_type* vertices, size_t count),
		(vertices, count)
	);

	N_WRAP
	(
		dynamic_vertex_buffer,
		dynamic_vertex_buffer,
		(s_type* vertices, size_t count),
		(vertices, count)
	);

}
