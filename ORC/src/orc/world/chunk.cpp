#include "pch.h"
#include "chunk.h"
#include "sprite_batch.h"
#include "sprite_batch_constructor.h"

namespace orc
{
	//chunk::chunk(const std::vector<tile>& tiles) :
	//	m_grid{ 0 },
	//	m_tile_count(0)
	//{
	//	std::vector<sprite_batch_constructor> batches;
	//	// for each given tile
	//	for (const tile& t : tiles)
	//	{
	//		bool added = false;
	//		// check if any existing batches have room for current tile
	//		for (auto& batch : batches)
	//		{
	//			// current batch has room, add current tile to it
	//			if (added = batch.can_contain(t))
	//			{
	//				batch.add(t);
	//				break;
	//			}
	//		}
	//		// no existing batch has room, make a new one
	//		if (!added)
	//		{
	//			sprite_batch_constructor batch;
	//			batch.add(t);
	//			batches.push_back(batch);
	//		}
	//	}

	//	// create batches from computed constructors
	//	for (const auto& batch : batches)
	//		m_batches.push_back(sprite_batch(batch));
	//}
	chunk::chunk() :
		m_tile_count(0),
		m_grid{ 0 }
	{}
	chunk::chunk(mage::input_file& in) :
		m_tile_count(0),
		m_grid{ 0 }
	{
		load(in);
	}



	void chunk::save(mage::output_file& out) const
	{
		n::chunk::save(out);
		out.ulong(m_tile_count);
		out.write(m_grid, n::c::tiles_per_chunk);
	}
	void chunk::load(mage::input_file& in)
	{
		// TODO cleanup
		// this has to be rewritten here because n::chunk::load instantiates n::sprite_batches, but orc::chunk::load needs to instantiate orc::sprite_batches
		m_coords.x = in.uint();
		m_coords.y = in.uint();

		const size_t batch_count = in.ulong();
		m_batches.reserve(batch_count);
		for (size_t i = 0; i < batch_count; i++)
			m_batches.push_back(new sprite_batch(in));

		m_tile_count = in.ulong();
		in.read(m_grid, n::c::tiles_per_chunk);
	}
	void chunk::set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite)
	{
		MAGE_ASSERT(pos.x < n::c::tiles_per_chunk_side&& pos.y < n::c::tiles_per_chunk_side, "Invalid chunk coordinates <{}, {}>", pos.x, pos.y);
		MAGE_ASSERT(layer < n::c::layers_per_chunk, "Invalid chunk layer {}", layer);


		const size_t index = (layer * n::c::tiles_per_chunk_layer) + (pos.y * n::c::tiles_per_chunk_side) + pos.x;
		if (m_grid[index] == sprite->get_handle())
			return;

		m_grid[index] = sprite->get_handle();
		m_tile_count++;


		n::tile t =
		{
			sprite,
			{
				{ 1.f * pos.x, 1.f * pos.y },
				{
					1.f * pos.x + 1.f * sprite->get_w() / n::c::pixels_per_sprite_side,
					1.f * pos.y + 1.f * sprite->get_h() / n::c::pixels_per_sprite_side
				}
			}
		};
		bool added = false;
		for (auto& batch : m_batches)
		{
			// TODO
			if (added = batch->can_contain(sprite))
			{
				batch->add_tile(t);
				break;
			}
		}

		// no room in existing batches, make a new batch
		if (!added)
		{
			sprite_batch* batch = new sprite_batch();
			MAGE_ASSERT(batch->can_contain(t.sprite), "Invalid tile");
			batch->add_tile(t);
			m_batches.push_back(batch);
		}
	}
}
