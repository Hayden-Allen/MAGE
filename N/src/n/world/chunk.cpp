#include "pch.h"
#include "chunk.h"

namespace n
{
	void chunk::draw(const mage::timestep& t, mage::game::sprite_bank* const sb, const mage::game::sprite_atlas_bank* const ab, const shader_program& shader)
	{
		// draw all tiles in this chunk
		for (sprite_batch& batch : m_batches)
			batch.draw(t, sb, ab, shader);
	}
}
