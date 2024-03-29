#include "pch.h"
#include "sprite_batch.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	sprite_batch::sprite_batch(sprite_batch_bank& bank, const glm::uvec2& base) :
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>(base),
		m_handle(bank.add(this)),
		m_next_tile(0)
	{
		resize();
	}



	void sprite_batch::build(coga::output_file& out) const
	{
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::save(out);
	}
	void sprite_batch::save(coga::output_file& out) const
	{
		build(out);
		out.ulong(m_max_tile_count).ulong(m_next_tile);
		out.uint(m_handle);
	}
	void sprite_batch::load(coga::input_file& in)
	{
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::load(in);
		m_max_tile_count = in.ulong();
		m_next_tile = in.ulong();
		m_handle = in.uint();
	}
	bool sprite_batch::can_contain(const sprite* const s) const
	{
		size_t additional = 0;
		for (const auto& a : s->get_atlases())
			additional += !m_atlases.contains(a);
		return (m_atlases.size() + additional) <= COGA_MTU;
	}
	size_t sprite_batch::add_tile(const sprite_bank& sb, const mage::tile& t)
	{
		// increase storage if this batch is already full
		if (is_full())
		{
			m_max_tile_count *= 2;
			COGA_ASSERT(m_max_tile_count < mage::c::sprite_batch_max_size, "Chunk is full");
			resize();
		}

		const auto& s = sb.get(t.sprite);
		// insert new atlases if necessary and increment counter
		for (const auto& a : s->get_atlases())
			add_atlas(a);
		// insert new sprite + sprite index if necessary
		const auto& handle = t.sprite;
		add_sprite(handle);
		if (!m_sprite_indices.contains(handle))
			m_sprite_indices.insert({ handle, m_sprite_indices.size() });

		// generate vertex data for new tile
		const size_t index = get_next();
		const size_t offset = index * mage::c::floats_per_tile;
		float vertices[mage::c::floats_per_tile];
		mage::gen_tile_vertices(sb, t, vertices, m_sprite_indices[handle], m_base_coords);
		m_vertices->update(vertices, mage::c::floats_per_tile, offset);

		// only increment count if the new tile was added to a non-opening
		m_next_tile += (index == m_next_tile);
		return offset;
	}
	void sprite_batch::delete_tile(const sprite* const s, size_t offset)
	{
		delete_tile(offset);

		// TODO
		//// remove now-unused atlases
		//for (const auto& a : s->get_atlases())
		//{
		//	auto& ref = m_atlas_counts[a];
		//	ref--;
		//	if (ref == 0)
		//	{
		//		m_atlas_counts.erase(ref);
		//		m_atlases.erase(a);
		//	}
		//}

		//// remove now-unused sprite
		//auto& ref = m_sprite_counts[s->get_handle()];
		//ref--;
		//if (ref == 0)
		//	m_sprite_counts.erase(ref);
	}


	
	void sprite_batch::resize()
	{
		delete m_indices;
		delete m_vertex_array;

		create_indices();

		const size_t vertex_count = m_max_tile_count * mage::c::vertices_per_tile * mage::c::floats_per_tile_vertex;

		if (m_vertices)
			m_vertices->resize(vertex_count);
		else
		{
			float* vertices = new float[vertex_count];
			coga::arrset(vertex_count, vertices, 0.f);
			m_vertices = new mage::retained_dynamic_vertex_buffer(vertices, vertex_count);
			delete[] vertices;
		}

		create_array();
	}
	size_t sprite_batch::get_next() const
	{
		size_t i = m_next_tile;
		if (!m_openings.empty())
		{
			i = m_openings.back();
			m_openings.pop_back();
		}
		return i;
	}
	void sprite_batch::add_sprite(sprite_bank::handle s)
	{
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::add_sprite(s, false);
		if (!m_sprite_counts.contains(s))
			m_sprite_counts.insert({ s, 0 });
		m_sprite_counts[s]++;
	}
	void sprite_batch::remove_sprite(sprite_bank::handle s)
	{
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::remove_sprite(s);

		auto& ref = m_sprite_counts[s];
		ref--;
		if (ref == 0)
			m_sprite_counts.erase(s);
	}
	void sprite_batch::add_atlas(sprite_atlas_bank::handle atlas)
	{
		mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::add_atlas(atlas);

		if (!m_atlas_counts.contains(atlas))
			m_atlas_counts.insert({ atlas, 0 });
		m_atlas_counts[atlas]++;
	}
	void sprite_batch::delete_tile(size_t offset)
	{
		float vertices[mage::c::floats_per_tile] = { 0.f };
		m_vertices->update(vertices, mage::c::floats_per_tile, offset);
		m_openings.push_back(offset / mage::c::floats_per_tile);
	}
}
