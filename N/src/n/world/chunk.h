#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"

namespace n
{
	class chunk final
	{
	public:
		chunk(const std::vector<tile>& tiles);
		N_DCM(chunk);


		void draw(const timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader);
	private:
		// 3 foreground 3 background
		constexpr static size_t s_layer_count = 6;


		std::vector<sprite_batch> m_batches;
	};
}
