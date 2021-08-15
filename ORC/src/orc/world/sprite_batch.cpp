#include "pch.h"
#include "sprite_batch.h"

namespace orc
{
	sprite_batch::sprite_batch(const sprite_batch_constructor& constructor)
	{
		m_sprite_count = constructor.m_tiles.size();
		m_sprites = new n::sprite_bank::handle[m_sprite_count];
		m_offsets = new glm::vec2[m_sprite_count];
		m_texture_indices = new int[m_sprite_count];


		// map sprite_atlas_bank indices to the texture index they will always be bound to
		for (const auto& a : constructor.m_atlases)
			m_atlases.insert({ a, m_atlases.size() });


		// map sprite pointer to its local index
		std::unordered_map<n::sprite*, size_t> sprite_indices;
		// total number of tiles, number of sprites added
		size_t tile_count = 0, sprite_index = 0;
		for (const auto& group : constructor.m_tiles)
		{
			// local index for current sprite
			sprite_indices.insert({ group.first, sprite_index });
			// store sprite_bank index of current sprite
			m_sprites[sprite_index] = group.first->get_handle();
			tile_count += group.second.size();
			sprite_index++;
		}


		uint32_t* indices = n::gen_indices(tile_count);
		m_indices = new n::static_index_buffer(indices, tile_count);
		delete[] indices;


		/**
		 * TODO generate only midpoints and use geometry shader?
		 */
		 // total number of floats needed for all vertices
		const size_t float_count = tile_count * n::c::vertices_per_tile * n::c::floats_per_tile_vertex;
		float* vertices = new float[float_count];
		// base index of the current vertex
		size_t index = 0;
		// for each sprite + tile list
		for (const auto& group : constructor.m_tiles)
		{
			// get the local index of the current sprite
			const float local_index = MAGE_CAST(float, sprite_indices[group.first]);
			const auto& base_coords = group.first->get_base_coords();
			// for each tile that uses the current sprite
			for (const tile& t : group.second)
			{
				// (x, y) offsets
				const float x[n::c::vertices_per_tile] = { t.pos.min.x, t.pos.max.x, t.pos.max.x, t.pos.min.x };
				const float y[n::c::vertices_per_tile] = { t.pos.min.y, t.pos.min.y, t.pos.max.y, t.pos.max.y };
				// (s, t) offsets
				const float tx[n::c::vertices_per_tile] = { base_coords.x.get_min(), base_coords.x.get_max(), base_coords.x.get_max(), base_coords.x.get_min() };
				const float ty[n::c::vertices_per_tile] = { base_coords.y.get_min(), base_coords.y.get_min(), base_coords.y.get_max(), base_coords.y.get_max() };

				// 4 vertices of (x, y), (s, t), (i) 
				for (size_t i = 0; i < n::c::vertices_per_tile; i++)
				{
					vertices[index * n::c::floats_per_tile_vertex + 0] = x[i];
					vertices[index * n::c::floats_per_tile_vertex + 1] = y[i];
					vertices[index * n::c::floats_per_tile_vertex + 2] = tx[i];
					vertices[index * n::c::floats_per_tile_vertex + 3] = ty[i];
					vertices[index * n::c::floats_per_tile_vertex + 4] = local_index;
					index++;
				}
			}
		}
		m_vertices = new n::static_vertex_buffer(vertices, float_count);
		delete[] vertices;


		// (x, y), (s, t), (i)
		m_vertex_array = new n::static_vertex_array(m_vertices,
			{
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float1
			}
		);
	}
}
