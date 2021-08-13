#include "pch.h"
#include "sprite_batch.h"
#include "n/graphics/sprite.h"

namespace n
{

	bool sprite_batch_constructor::can_contain(const tile& t) const
	{
		// compute the number of atlases that the given tile's sprite uses that are not already part of this batch
		size_t additional = 0;
		for (const auto& a : t.sprite->get_atlases())
			additional += !m_atlases.contains(a);
		// if adding the required atlases for the given tile would result in this batch having more atlases than can bound at a time, reject the tile
		return (m_atlases.size() + additional) <= get_max_atlas_count();
	}
	void sprite_batch_constructor::add(const tile& t)
	{
		// add any new atlases (m_atlases is a set)
		const auto& atlases = t.sprite->get_atlases();
		m_atlases.insert(atlases.begin(), atlases.end());

		// add given tile to its sprite's list of tiles, or create a list if it doesn't exist
		const auto& it = m_tiles.find(t.sprite);
		if (it != m_tiles.end())
			it->second.push_back(t);
		else
			m_tiles.insert({ t.sprite, { t } });
	}



	sprite_batch::sprite_batch(const sprite_batch_constructor& constructor) :
		m_indices(nullptr),
		m_vertices(nullptr),
		m_vertex_array(nullptr),
		m_sprite_count(constructor.m_tiles.size()),
		m_sprites(new sprite_bank::handle[m_sprite_count]),
		m_offsets(new glm::vec2[m_sprite_count]),
		m_texture_indices(new int[m_sprite_count])
	{
		// map sprite_atlas_bank indices to the texture index they will always be bound to
		for (const auto& a : constructor.m_atlases)
			m_atlases.insert({ a, m_atlases.size() });


		// map sprite pointer to its local index
		std::unordered_map<sprite*, size_t> sprite_indices;
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


		uint32_t* indices = gen_indices(tile_count);
		m_indices = new static_index_buffer(indices, tile_count);
		delete[] indices;


		/**
		 * TODO generate only midpoints and use geometry shader?
		 */
		// total number of floats needed for all vertices
		const size_t float_count = tile_count * c::vertices_per_tile * c::floats_per_tile_vertex;
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
				const float x[c::vertices_per_tile] = { t.pos.min.x, t.pos.max.x, t.pos.max.x, t.pos.min.x };
				const float y[c::vertices_per_tile] = { t.pos.min.y, t.pos.min.y, t.pos.max.y, t.pos.max.y };
				// (s, t) offsets
				const float tx[c::vertices_per_tile] = { base_coords.x.get_min(), base_coords.x.get_max(), base_coords.x.get_max(), base_coords.x.get_min() };
				const float ty[c::vertices_per_tile] = { base_coords.y.get_min(), base_coords.y.get_min(), base_coords.y.get_max(), base_coords.y.get_max() };

				// 4 vertices of (x, y), (s, t), (i) 
				for (size_t i = 0; i < c::vertices_per_tile; i++)
				{
					vertices[index * c::floats_per_tile_vertex + 0] = x[i];
					vertices[index * c::floats_per_tile_vertex + 1] = y[i];
					vertices[index * c::floats_per_tile_vertex + 2] = tx[i];
					vertices[index * c::floats_per_tile_vertex + 3] = ty[i];
					vertices[index * c::floats_per_tile_vertex + 4] = local_index;
					index++;
				}
			}
		}
		m_vertices = new static_vertex_buffer(vertices, float_count);
		delete[] vertices;


		// (x, y), (s, t), (i)
		m_vertex_array = new static_vertex_array(m_vertices,
			{
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float2,
				mage::gfx::shader_type::float1
			}
		);
	}
	sprite_batch::~sprite_batch()
	{
		delete m_indices;
		delete m_vertices;
		delete m_vertex_array;
		delete m_sprites;
		delete m_offsets;
		delete m_texture_indices;
	}



	void sprite_batch::draw(const timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader)
	{
		// for each sprite in this batch
		for (size_t i = 0; i < m_sprite_count; i++)
		{
			// update the current sprite
			sprite* const s = sb->get(m_sprites[i]);
			s->update(t);

			const auto& state = s->get_current_frame();
			// get texture coord offsets for current frame
			m_offsets[i] = state.offset;
			// get atlas index for current frame. This is used by the shader as an index into m_texture_indices, which in turn yields the actual texture slot that this bank is bound to
			m_texture_indices[i] = state.bank;
		}
		// bind all atlases to their pre-determined indices
		for (const auto& pair : m_atlases)
			ab->get(pair.first)->bind(MAGE_CAST(uint32_t, pair.second));

		// upload current arrays
		shader.set_uniform_int_array(c::shader_sprite_to_texture_indices, m_texture_indices, m_sprite_count);
		shader.set_uniform_float2_array(c::shader_sprite_offsets, m_offsets, m_sprite_count);
		
		// draw all tiles
		mage::gfx::renderer::draw(m_indices, m_vertex_array);
	}
}
