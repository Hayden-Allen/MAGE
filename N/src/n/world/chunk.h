#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"

namespace n
{
	class chunk
	{
	public:
		chunk() :
			m_coords({ 0.f, 0.f })
		{
			// TODO
		}
		N_DCM(chunk);


		void draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader);
	protected:
		std::vector<sprite_batch> m_batches;
		glm::vec2 m_coords;
	};
}
