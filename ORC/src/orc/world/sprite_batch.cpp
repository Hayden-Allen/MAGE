#include "pch.h"
#include "sprite_batch.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	sprite_batch::sprite_batch(sprite_batch_bank& bank, const glm::uvec2& base) :
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>(base),
		m_handle(bank.add(this)),
		m_max_tile_count(n::c::sprite_batch_base_size),
		m_next_tile(0)
	{
		resize();
	}



	void sprite_batch::save(mage::output_file& out) const
	{
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::save(out);
		out.ulong(m_max_tile_count).ulong(m_next_tile);

		out.ulong(m_sprite_indices.size());
		for (const auto& pair : m_sprite_indices)
			out.ushort(pair.first).ulong(pair.second);

		m_vertices->save(out);

		out.uint(m_handle);
	}
	void sprite_batch::load(mage::input_file& in)
	{
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::load(in);
		m_max_tile_count = in.ulong();
		m_next_tile = in.ulong();

		const size_t sprite_count = in.ulong();
		m_sprite_indices.reserve(sprite_count);
		for (size_t i = 0; i < sprite_count; i++)
			m_sprite_indices.insert({ in.ushort(), in.ulong() });

		create_indices();
		m_vertices = new n::retained_dynamic_vertex_buffer(in);
		create_array();

		m_handle = in.uint();
	}
	bool sprite_batch::can_contain(const sprite* const s) const
	{
		size_t additional = 0;
		for (const auto& a : s->get_atlases())
			additional += !m_atlases.contains(a);
		return (m_atlases.size() + additional) <= MAGE_MTU;
	}
	size_t sprite_batch::add_tile(const sprite_bank& sb, const n::tile& t)
	{
		// increase storage if this batch is already full
		if (is_full())
		{
			m_max_tile_count *= 2;
			MAGE_ASSERT(m_max_tile_count < n::c::sprite_batch_max_size, "Chunk is full");
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
		const size_t offset = index * n::c::floats_per_tile;
		float vertices[n::c::floats_per_tile];
		n::gen_tile_vertices(sb, t, vertices, m_sprite_indices[handle], m_base_coords);
		m_vertices->update(vertices, n::c::floats_per_tile, offset);

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

		const size_t vertex_count = m_max_tile_count * n::c::vertices_per_tile * n::c::floats_per_tile_vertex;

		if (m_vertices)
			m_vertices->resize(vertex_count);
		else
		{
			float* vertices = new float[vertex_count];
			mage::arrset(vertex_count, vertices, 0.f);
			m_vertices = new n::retained_dynamic_vertex_buffer(vertices, vertex_count);
			delete[] vertices;
		}

		create_array();
	}
	void sprite_batch::create_indices()
	{
		// gen new index buffer. TODO make retained?
		uint32_t* indices = n::gen_indices(m_max_tile_count);
		m_indices = new n::static_index_buffer(indices, m_max_tile_count);
		delete[] indices;
	}
	void sprite_batch::create_array()
	{
		// (x, y), (s, t), (i)
		m_vertex_array = new n::dynamic_vertex_array(m_vertices,
			{
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float1
			}
		);
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
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::add_sprite(s);
		if (!m_sprite_counts.contains(s))
			m_sprite_counts.insert({ s, 0 });
		m_sprite_counts[s]++;
	}
	void sprite_batch::remove_sprite(sprite_bank::handle s)
	{
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::remove_sprite(s);

		auto& ref = m_sprite_counts[s];
		ref--;
		if (ref == 0)
			m_sprite_counts.erase(s);
	}
	void sprite_batch::add_atlas(sprite_atlas_bank::handle atlas)
	{
		n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::add_atlas(atlas);

		if (!m_atlas_counts.contains(atlas))
			m_atlas_counts.insert({ atlas, 0 });
		m_atlas_counts[atlas]++;
	}
	void sprite_batch::delete_tile(size_t offset)
	{
		float vertices[n::c::floats_per_tile] = { 0.f };
		m_vertices->update(vertices, n::c::floats_per_tile, offset);
		m_openings.push_back(offset / n::c::floats_per_tile);
	}
}
