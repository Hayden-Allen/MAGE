#include "pch.h"
#include "dynamic.h"
#include "dynamic_batch.h"
#include "dynamic_list.h"
#include "n/graphics/sprite.h"

namespace n
{
	dynamic_batch::dynamic_batch() :
		mage::indexed_list<size_t, size_t, size_t, size_t>(MAGE_MTU, c::dynamic_list_size),
		m_index(0),
		m_indices(new MAGE_RAN::dynamic_index_buffer(MAGE_MTU* c::indices_per_tile))
	{
		m_sprites.reserve(MAGE_MTU);
		for (size_t i = 0; i < m_count; i++)
			m_sprites.push_back(nullptr);
	}



	size_t dynamic_batch::add(size_t dynamic)
	{
		// add to list
		const size_t index = add_base(dynamic);

		// generate and upload index data
		constexpr size_t count = c::indices_per_tile;
		uint32_t indices[count];
		for (size_t i = 0; i < count; i++)
			indices[i] = N_CAST(uint32_t, dynamic * c::vertices_per_tile + c::index_buffer_offsets[i]);
		m_indices->update(indices, count, index * count);

		return index;
	}
	void dynamic_batch::remove(size_t dynamic)
	{
		remove_base(dynamic);

		// fill given dynamic's index data with 0's
		constexpr size_t count = c::indices_per_tile;
		uint32_t indices[count] = { 0 };
		m_indices->update(indices, count, dynamic * count);
	}
	void dynamic_batch::move(dynamic_list& list, float dt) const
	{
		for_each([&list, dt](size_t i) { list.m_list[i]->update(dt); });
	}
	void dynamic_batch::draw(dynamic_list& list) const
	{
		for (size_t i = 0; i < get_next(); i++)
		{
			sprite* s = nullptr;
			if (is_valid(i))
				s = list.m_list[m_list[i]]->get_state();
			m_sprites[i] = s;
		}
	}
}
