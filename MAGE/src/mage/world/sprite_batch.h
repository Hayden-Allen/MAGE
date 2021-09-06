#pragma once
#include "pch.h"
#include "tile.h"
#include "mage/graphics/wrap/buffer.h"
#include "mage/graphics/wrap/shader_program.h"
#include "mage/graphics/wrap/vertex_array.h"

namespace mage
{
	template<typename IB, typename VB, typename VA, typename SPRITE, typename BANK>
	class sprite_batch_base : public coga::serializable
	{
	public:
		COGA_DC(sprite_batch_base);
		sprite_batch_base(sprite_batch_base&& other) noexcept :
			m_indices(other.m_indices),
			m_vertices(other.m_vertices),
			m_vertex_array(other.m_vertex_array),
			m_atlases(other.m_atlases),
			m_sprites(other.m_sprites),
			m_offsets(other.m_offsets),
			m_texture_indices(other.m_texture_indices),
			m_sprite_indices(other.m_sprite_indices),
			m_base_coords(other.m_base_coords),
			m_max_tile_count(other.m_max_tile_count)
		{
			other.m_indices = nullptr;
			other.m_vertices = nullptr;
			other.m_vertex_array = nullptr;
		}
		virtual ~sprite_batch_base()
		{
			delete m_indices;
			delete m_vertices;
			delete m_vertex_array;
		}
	public:
		virtual bool can_contain(const SPRITE* const s) const = 0;
		virtual size_t add_tile(const BANK& sb, const tile& t) = 0;
		virtual void delete_tile(size_t offset) = 0;
		virtual void save(coga::output_file& out) const override
		{
			m_vertices->save(out);

			out.ulong(m_atlases.size());
			for (const auto& pair : m_atlases)
				out.ushort(pair.first).ulong(pair.second);

			out.ulong(m_sprites.size());
			for (const auto& s : m_sprites)
				out.ushort(s);

			out.ulong(m_offsets.size());
			for (const auto& o : m_offsets)
				out.uint(COGA_PUN(uint32_t, o.x)).uint(COGA_PUN(uint32_t, o.y));

			out.ulong(m_texture_indices.size());
			for (const auto& i : m_texture_indices)
				out.uint(i);

			out.ulong(m_sprite_indices.size());
			for (const auto& pair : m_sprite_indices)
				out.ushort(pair.first).ulong(pair.second);

			out.uint(m_base_coords.x).uint(m_base_coords.y);

			out.ulong(m_max_tile_count);
		}
		virtual void load(coga::input_file& in) override
		{
			create_indices();
			m_vertices = new VB(in);
			create_array();

			const size_t atlas_count = in.ulong();
			m_atlases.reserve(atlas_count);
			for (size_t i = 0; i < atlas_count; i++)
				m_atlases.insert({ in.ushort(), in.ulong() });

			const size_t sprite_count = in.ulong();
			m_sprites.reserve(sprite_count);
			for (size_t i = 0; i < sprite_count; i++)
				add_sprite(in.ushort(), true);

			const size_t offset_count = in.ulong();
			m_offsets.reserve(offset_count);
			for (size_t i = 0; i < offset_count; i++)
			{
				uint32_t x = in.uint(), y = in.uint();
				m_offsets.push_back({ COGA_PUN(float, x), COGA_PUN(float, y) });
			}

			const size_t texture_index_count = in.ulong();
			m_texture_indices.reserve(texture_index_count);
			for (size_t i = 0; i < texture_index_count; i++)
				m_texture_indices.push_back(COGA_CAST(int, in.uint()));

			const size_t sprite_index_count = in.ulong();
			m_sprite_indices.reserve(sprite_index_count);
			for (size_t i = 0; i < sprite_index_count; i++)
				m_sprite_indices.insert({ in.ushort(), in.ulong() });

			m_base_coords = { in.uint(), in.uint() };
			m_max_tile_count = in.ulong();
		}
		template<typename SAB>
		void draw(const coga::timestep& t, BANK* const sb, const SAB* const ab, const shader_program& shader)
		{
			// for each sprite in this batch
			for (size_t i = 0; i < m_sprites.size(); i++)
			{
				// update the current sprite
				sprite* const s = sb->get(m_sprites[i]);
				s->update(t);

				const auto& state = s->get_current_frame();
				// get texture coord offsets for current frame
				m_offsets[i] = state.offset;
				// get the texture index of the atlas that the current frame is stored in
				m_texture_indices[i] = COGA_CAST(int, m_atlases.at(state.bank));
			}
			// bind all atlases to their pre-determined indices
			for (const auto& pair : m_atlases)
				ab->get(pair.first)->bind(COGA_CAST(uint32_t, pair.second));

			shader.bind();
			// upload current arrays
			shader.set_uniform_int_array(c::shader_sprite_to_texture_indices, m_texture_indices.data(), m_texture_indices.size());
			shader.set_uniform_float2_array(c::shader_sprite_offsets, m_offsets.data(), m_offsets.size());

			// draw all tiles
			coga::gfx::renderer::draw(m_indices, m_vertex_array);
		}
	protected:
		IB* m_indices;
		VB* m_vertices;
		VA* m_vertex_array;
		// maps atlas handles to the texture slot to which they will always be bound. Each batch can have up to COGA_MTU atlases. 
		std::unordered_map<sprite_atlas_bank::handle, size_t> m_atlases;
		// all the sprites that the tiles in this batch use
		std::vector<sprite_bank::handle> m_sprites;
		// current texture coord offsets for each sprite
		std::vector<glm::vec2> m_offsets;
		// texture slot to which each sprite is bound
		std::vector<int> m_texture_indices;
		// maps a sprite handle to its index in m_sprites, m_offsets, and m_texture_indices
		std::unordered_map<sprite_bank::handle, size_t> m_sprite_indices;
		// come from the chunk that this batch is a part of
		glm::uvec2 m_base_coords;
		size_t m_max_tile_count;
	protected:
		sprite_batch_base(const glm::uvec2& base) :
			m_indices(nullptr),
			m_vertices(nullptr),
			m_vertex_array(nullptr),
			m_base_coords(base),
			m_max_tile_count(mage::c::sprite_batch_base_size)
		{}
	protected:
		// TODO
		virtual void add_sprite(sprite_bank::handle sprite, bool file)
		{
			// only insert if new
			if (!m_sprite_indices.contains(sprite))
			{
				m_sprite_indices.insert({ sprite, m_sprites.size() });
				m_sprites.push_back(sprite);
				if (!file)
				{
					m_offsets.push_back({ 0.f, 0.f });
					m_texture_indices.push_back(0);
				}
			}
		}
		// TODO
		virtual void remove_sprite(sprite_bank::handle sprite)
		{
			const auto& it = m_sprite_indices.find(sprite);
			COGA_ASSERT(it != m_sprite_indices.end(), "Cannot remove a sprite that doesn't exist");
			const size_t index = it->second;
			// erase only takes iterators. The index is guaranteed to be the same for all three arrays because of the way add_sprite works
			m_sprites.erase(m_sprites.begin() + index);
			m_offsets.erase(m_offsets.begin() + index);
			m_texture_indices.erase(m_texture_indices.begin() + index);
			m_sprite_indices.erase(sprite);
		}
		virtual void add_atlas(sprite_atlas_bank::handle atlas)
		{
			if(!m_atlases.contains(atlas))
				m_atlases.insert({ atlas, m_atlases.size() });
		}
		void create_indices()
		{
			// gen new index buffer. TODO make retained?
			uint32_t* indices = mage::gen_indices(m_max_tile_count);
			m_indices = new IB(indices, m_max_tile_count);
			delete[] indices;
		}
		void create_array()
		{
			// (x, y), (s, t), (i)
			m_vertex_array = new VA(m_vertices,
				{
					coga::gfx::shader_type::float2,
					coga::gfx::shader_type::float2,
					coga::gfx::shader_type::float1
				}
			);
		}
	};



	class sprite_batch final : public sprite_batch_base<static_index_buffer, static_vertex_buffer, static_vertex_array, sprite, sprite_bank>
	{
	public:
		// static gl stuff
		sprite_batch(coga::input_file& in) :
			sprite_batch_base({ 0, 0 })
		{
			load(in);
		}
		COGA_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			sprite_batch_base(std::move(other))
		{}
	public:
		void save(coga::output_file& out) const override
		{
			COGA_ASSERT(false, "Cannot save a mage::sprite_batch");
		}
		bool can_contain(const sprite* const s) const override
		{
			COGA_ASSERT(false, "Cannot update an mage::sprite_batch");
			return false;
		}
		size_t add_tile(const mage::sprite_bank& sb, const tile& t) override
		{
			COGA_ASSERT(false, "Cannot update an mage::sprite_batch");
			return 0;
		}
		void delete_tile(size_t offset)
		{
			COGA_ASSERT(false, "Cannot update an mage::sprite_batch");
		}
	};
}
