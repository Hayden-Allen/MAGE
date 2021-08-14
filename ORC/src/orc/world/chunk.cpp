#include "pch.h"
#include "chunk.h"
#include "sprite_batch.h"
#include "sprite_batch_constructor.h"

namespace orc
{
	chunk::chunk(const std::vector<tile>& tiles) :
		m_grid{ 0 },
		m_tile_count(0)
	{
		std::vector<sprite_batch_constructor> batches;
		// for each given tile
		for (const tile& t : tiles)
		{
			bool added = false;
			// check if any existing batches have room for current tile
			for (auto& batch : batches)
			{
				// current batch has room, add current tile to it
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

		// create batches from computed constructors
		for (const auto& batch : batches)
			m_batches.push_back(sprite_batch(batch));
	}
}
