#include "pch.h"
#include "sprite_batch.h"
#include "n/graphics/sprite.h"

namespace n
{

	bool sprite_batch_constructor::can_contain(const tile& t) const
	{
		size_t additional = 0;
		for (const auto& a : t.sprite->get_atlases())
			additional += !m_atlases.contains(a);
		return (m_atlases.size() + additional) <= get_max_atlas_count();
	}
	void sprite_batch_constructor::add(const tile& t)
	{
		const auto& atlases = t.sprite->get_atlases();
		m_atlases.insert(atlases.begin(), atlases.end());

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
		m_sprite_atlases(new sprite_atlas_bank::handle[mage::gfx::context::get_max_texture_units()]),
		m_offsets(new glm::vec2[mage::gfx::context::get_max_texture_units()])
	{
		// store atlas indices
		for (auto atlas : constructor.m_atlases)
			m_atlases.push_back(atlas);


		std::unordered_map<sprite*, size_t> sprite_indices;
		size_t tile_count = 0, sprite_index = 0;
		for (const auto& group : constructor.m_tiles)
		{
			sprite_indices.insert({ group.first, m_sprites.size() });
			m_sprites.push_back(group.first->get_handle());
			m_sprite_atlases[sprite_index] = group.first->get_current_frame().bank;
			m_offsets[sprite_index] = group.first->get_current_frame().offset;
			tile_count += group.second.size();
			sprite_index++;
		}


		const size_t index_count = tile_count * tile::s_indices;
		uint32_t* indices = new uint32_t[index_count];
		constexpr uint32_t offsets[] = { 0, 1, 2, 0, 2, 3 };
		for (size_t i = 0; i < index_count; i++)
			indices[i] = i / 6 * 4 + offsets[i % 6];
		m_indices = new static_index_buffer(indices, index_count);
		delete[] indices;


		const size_t vertex_count = tile_count * tile::s_vertices, float_count = vertex_count * tile::s_floats_per_vertex;
		float* vertices = new float[float_count];
		size_t index = 0;
		for (const auto& group : constructor.m_tiles)
		{
			const float local_index = MAGE_CAST(float, sprite_indices[group.first]);
			for (const tile& t : group.second)
			{
				const auto& c = t.sprite->get_base_coords();
				const float x[tile::s_vertices] = { t.pos.min.x, t.pos.max.x, t.pos.max.x, t.pos.min.x };
				const float y[tile::s_vertices] = { t.pos.min.y, t.pos.min.y, t.pos.max.y, t.pos.max.y };
				const float tx[tile::s_vertices] = { c.x.get_min(), c.x.get_max(), c.x.get_max(), c.x.get_min() };
				const float ty[tile::s_vertices] = { c.y.get_min(), c.y.get_min(), c.y.get_max(), c.y.get_max() };

				for (size_t i = 0; i < tile::s_vertices; i++)
				{
					vertices[index * tile::s_floats_per_vertex + 0] = x[i];
					vertices[index * tile::s_floats_per_vertex + 1] = y[i];
					vertices[index * tile::s_floats_per_vertex + 2] = tx[i];
					vertices[index * tile::s_floats_per_vertex + 3] = ty[i];
					vertices[index * tile::s_floats_per_vertex + 4] = local_index;
					index++;
				}
			}
		}
		m_vertices = new static_vertex_buffer(vertices, float_count);
		delete[] vertices;


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
		delete m_sprite_atlases;
		delete m_offsets;
	}



	void sprite_batch::draw(const timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader)
	{
		for (size_t i = 0; i < m_sprites.size(); i++)
		{
			sprite* const s = sb->get(m_sprites[i]);
			s->update(t);
			m_sprite_atlases[i] = s->get_current_frame().bank;
			m_offsets[i] = s->get_current_frame().offset;
		}
		for (size_t i = 0; i < m_atlases.size(); i++)
			ab->get(m_atlases[i])->bind(i);

		// for a sprite s, u_tex_indices[s.local_index] = the index to which s's current atlas is bound
		// shader.set_uniform_int_array("u_tex_indices", (const int*)m_sprite_atlases, mage::gfx::context::get_max_texture_units());
		shader.set_uniform_float2_array("u_offsets", m_offsets, mage::gfx::context::get_max_texture_units());

		mage::gfx::renderer::draw(m_indices, m_vertex_array);
	}
}
