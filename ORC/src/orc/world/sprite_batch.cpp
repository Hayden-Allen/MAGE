#include "pch.h"
#include "sprite_batch.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	sprite_batch::sprite_batch(const glm::uvec2& base) :
		n::sprite_batch_base(base),
		m_max_tile_count(n::c::sprite_batch_base_size),
		m_tile_count(0)
	{
		resize();
	}



	void sprite_batch::save(mage::output_file& out) const
	{
		n::sprite_batch_base::save(out);
		out.ulong(m_max_tile_count).ulong(m_tile_count);

		out.ulong(m_sprite_indices.size());
		for (const auto& pair : m_sprite_indices)
			out.ushort(pair.first).ulong(pair.second);

		((n::retained_dynamic_vertex_buffer*)m_vertices)->save(out);
	}
	void sprite_batch::load(mage::input_file& in)
	{
		n::sprite_batch_base::load(in);
		m_max_tile_count = in.ulong();
		m_tile_count = in.ulong();

		const size_t sprite_count = in.ulong();
		m_sprite_indices.reserve(sprite_count);
		for (size_t i = 0; i < sprite_count; i++)
			m_sprite_indices.insert({ in.ushort(), in.ulong() });

		create_indices();
		m_vertices = new n::retained_dynamic_vertex_buffer(in);
		create_array();
	}
	bool sprite_batch::can_contain(const n::sprite* const s) const
	{
		size_t additional = 0;
		for (const auto& a : ((sprite* const)s)->get_atlases())
			additional += !m_atlases.contains(a);
		return (m_atlases.size() + additional) <= MAGE_MTU;
	}
	void sprite_batch::add_tile(const n::tile& t)
	{
		// increase storage if this batch is already full
		if (m_tile_count == m_max_tile_count)
		{
			m_max_tile_count *= 2;
			MAGE_ASSERT(m_max_tile_count < n::c::sprite_batch_max_size, "Chunk is full");
			resize();
		}

		// insert new atlases if necessary
		for (const auto& a : ((sprite* const)t.sprite)->get_atlases())
		{
			if(!m_atlases.contains(a))
				m_atlases.insert({ a, m_atlases.size() });
		}
		// insert new sprite + sprite index if necessary
		const auto& handle = t.sprite->get_handle();
		if (!m_sprite_indices.contains(handle))
		{
			add_sprite(handle);
			m_sprite_indices.insert({ handle, m_sprite_indices.size() });
		}

		// generate vertex data for new tile
		const size_t index = m_sprite_indices[handle];
		const size_t offset = m_tile_count * n::c::floats_per_tile;
		float vertices[n::c::floats_per_tile];
		n::gen_tile_vertices(vertices, t, index, m_base_coords);
		m_vertices->update(vertices, n::c::floats_per_tile, offset);

		m_tile_count++;
	}


	
	void sprite_batch::resize()
	{
		delete m_indices;
		delete m_vertex_array;

		create_indices();

		// use existing VB to create new one. TODO make this cleaner (add resize function to buffer probably)
		const size_t vertex_count = m_max_tile_count * n::c::vertices_per_tile * n::c::floats_per_tile_vertex;

		if (m_vertices)
		{
			auto old_vertices = m_vertices;
			m_vertices = new n::retained_dynamic_vertex_buffer(N_PUN(n::retained_dynamic_vertex_buffer, *m_vertices), vertex_count);
			delete old_vertices;
		}
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
		// gen new index buffer. TODO make retained
		uint32_t* indices = n::gen_indices(m_max_tile_count);
		m_indices = new n::static_index_buffer(indices, m_max_tile_count);
		delete[] indices;
	}
	void sprite_batch::create_array()
	{
		// (x, y), (s, t), (i)
		m_vertex_array = new n::dynamic_vertex_array((n::dynamic_vertex_buffer*)m_vertices,
			{
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float1
			}
		);
	}
}
