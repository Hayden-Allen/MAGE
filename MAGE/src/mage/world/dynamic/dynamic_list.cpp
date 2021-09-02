#include "pch.h"
#include "dynamic_list.h"
#include "dynamic.h"
#include "dynamic_batch.h"

namespace mage
{
	dynamic_list::dynamic_list() :
		coga::indexed_list<dynamic*, dynamic_list_handle, dynamic* const, dynamic* const>(c::dynamic_list_size, nullptr),
		m_vertex_buffer(new COGA_RAN::dynamic_vertex_buffer(nullptr, c::dynamic_list_size & c::floats_per_dynamic)),
		m_vertex_array(new COGA_RAN::dynamic_vertex_array(m_vertex_buffer,
			{
				// x, y
				coga::gfx::shader_type::float2,
				// s, t
				coga::gfx::shader_type::float2,
				// i
				coga::gfx::shader_type::float1,
				// cy
				coga::gfx::shader_type::float1
			})),
		// each group contains up to COGA_MTU dynamics
		m_batches(c::dynamic_list_size / COGA_MTU)
	{}
	dynamic_list::~dynamic_list()
	{
		for (size_t i = 0; i < get_next(); i++)
			delete m_list[i];
		delete m_vertex_buffer;
		delete m_vertex_array;
	}



	dynamic_list_handle dynamic_list::add(dynamic* const d)
	{
		// index in this list
		const size_t index = add_base(d);

		// index of the containing batch in m_batches
		// local (texture) index within the containing batch
		size_t batch_index = 0, texture_index = 0;
		bool found = false;
		for (size_t i = 0; m_batches.get_next(); i++)
		{
			dynamic_batch* const batch = m_batches[i];
			// if current batch exists and has room, add to it
			if (batch && !batch->is_full())
			{
				batch_index = i;
				texture_index = batch->add(index);
				found = true;
				break;
			}
		}

		// existing batches are full, create new one
		if (!found)
		{
			dynamic_batch* const batch = new dynamic_batch();
			texture_index = batch->add(index);
			batch_index = batch->m_index = m_batches.add(batch);
		}

		return { index, batch_index, texture_index };
	}
	void dynamic_list::remove(dynamic* const d)
	{
		const auto& indices = d->m_handle;
		remove_base(indices.list);

		dynamic_batch* const batch = m_batches[indices.batch];
		batch->remove(indices.texture);

		if (batch->is_empty())
			m_batches.remove(batch->m_index);
	}
	void dynamic_list::draw()
	{
		m_batches.for_each([this](dynamic_batch* const batch) { batch->draw(*this); });
	}
	void dynamic_list::update(float dt)
	{
		// run_scripts
		m_batches.for_each([this, dt](dynamic_batch* const batch) { batch->move(*this, dt); });
		// move_hitboxes
		// resolve_collisions
	}
	void dynamic_list::update_one(size_t i)
	{
		COGA_ASSERT(is_valid(i), "Cannot update invalid dynamic {}", i);
		m_vertex_array->get_buffer().update(m_list[i]->get_vertices(), c::floats_per_dynamic, i * c::floats_per_dynamic);
	}
}
