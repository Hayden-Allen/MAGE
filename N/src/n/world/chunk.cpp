#include "pch.h"
#include "chunk.h"

namespace n
{
	chunk::chunk(const std::vector<tile>& tiles)
	{
		std::vector<sprite_batch_constructor> batches;
		for (const tile& t : tiles)
		{
			bool added = false;
			for (auto& batch : batches)
			{
				if (added = batch.can_contain(t))
				{
					batch.add(t);
					break;
				}
			}
			// no existing batch has room, make a new one
			if (!added)
			{
				sprite_batch_constructor batch;
				batch.add(t);
				batches.push_back(batch);
			}
		}

		for (const auto& batch : batches)
			m_batches.emplace_back(batch);
	}



	void chunk::draw(const timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader)
	{
		for (sprite_batch& batch : m_batches)
			batch.draw(t, sb, ab, shader);
	}
}
