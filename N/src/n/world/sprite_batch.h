#pragma once
#include "pch.h"
#include "tile.h"
#include "n/graphics/wrap/buffer.h"
#include "n/graphics/wrap/shader_program.h"
#include "n/graphics/wrap/vertex_array.h"

namespace n
{
	template<typename IB, typename VB, typename VA, typename SPRITE, typename BANK>
	class sprite_batch_base : public mage::serializable
	{
	public:
		MAGE_DC(sprite_batch_base);
		sprite_batch_base(sprite_batch_base&& other) noexcept :
			m_indices(other.m_indices),
			m_vertices(other.m_vertices),
			m_vertex_array(other.m_vertex_array),
			m_atlases(other.m_atlases),
			m_sprites(other.m_sprites),
			m_offsets(other.m_offsets),
			m_texture_indices(other.m_texture_indices),
			m_base_coords(other.m_base_coords)
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
		virtual void save(mage::output_file& out) const override
		{
			const size_t atlas_count = m_atlases.size();
			out.ulong(atlas_count);
			for (const auto& pair : m_atlases)
				out.ushort(pair.first).ulong(pair.second);

			out.ulong(m_sprites.size());
			for (const auto& s : m_sprites)
				out.ushort(s);

			out.ulong(m_offsets.size());
			out.ulong(m_texture_indices.size());
		}
		virtual void load(mage::input_file& in) override
		{
			const size_t atlas_count = in.ulong();
			m_atlases.reserve(atlas_count);
			for (size_t i = 0; i < atlas_count; i++)
				m_atlases.insert({ in.ushort(), in.ulong() });

			const size_t sprite_count = in.ulong();
			m_sprites.reserve(sprite_count);
			for (size_t i = 0; i < sprite_count; i++)
				add_sprite(in.ushort());

			m_offsets = std::vector<glm::vec2>(in.ulong());
			m_texture_indices = std::vector<int>(in.ulong());
		}
		template<typename SAB>
		void draw(const mage::timestep& t, BANK* const sb, const SAB* const ab, const shader_program& shader)
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
				m_texture_indices[i] = N_CAST(int, m_atlases.at(state.bank));
			}
			// bind all atlases to their pre-determined indices
			for (const auto& pair : m_atlases)
				ab->get(pair.first)->bind(MAGE_CAST(uint32_t, pair.second));

			// upload current arrays
			shader.set_uniform_int_array(c::shader_sprite_to_texture_indices, m_texture_indices.data(), m_texture_indices.size());
			shader.set_uniform_float2_array(c::shader_sprite_offsets, m_offsets.data(), m_offsets.size());

			// draw all tiles
			mage::gfx::renderer::draw(m_indices, m_vertex_array);
		}
	protected:
		IB* m_indices;
		VB* m_vertices;
		VA* m_vertex_array;
		std::unordered_map<sprite_atlas_bank::handle, size_t> m_atlases;
		// TODO condense into a map
		std::vector<sprite_bank::handle> m_sprites;
		std::vector<glm::vec2> m_offsets;
		std::vector<int> m_texture_indices;
		glm::uvec2 m_base_coords;
	protected:
		sprite_batch_base(const glm::uvec2& base) :
			m_indices(nullptr),
			m_vertices(nullptr),
			m_vertex_array(nullptr),
			m_base_coords(base)
		{}
	protected:
		virtual void add_sprite(sprite_bank::handle sprite)
		{
			// TODO properly
			// only insert if new
			if (std::find(m_sprites.begin(), m_sprites.end(), sprite) == m_sprites.end())
			{
				m_sprites.push_back(sprite);
				m_offsets.push_back({ 0.f, 0.f });
				m_texture_indices.push_back(0);
			}
		}
		virtual void remove_sprite(sprite_bank::handle sprite)
		{
			// TODO properly
			const size_t index = std::find(m_sprites.begin(), m_sprites.end(), sprite) - m_sprites.begin();
			m_sprites.erase(m_sprites.begin() + index);
			m_offsets.erase(m_offsets.begin() + index);
			m_texture_indices.erase(m_texture_indices.begin() + index);
		}
		virtual void add_atlas(sprite_atlas_bank::handle atlas)
		{
			if(!m_atlases.contains(atlas))
				m_atlases.insert({ atlas, m_atlases.size() });
		}
	};



	class sprite_batch final : public sprite_batch_base<static_index_buffer, static_vertex_buffer, static_vertex_array, sprite, sprite_bank>
	{
	public:
		// static gl stuff
		sprite_batch(mage::input_file& in) :
			sprite_batch_base({ 0, 0 })
		{
			load(in);
		}
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			sprite_batch_base(std::move(other))
		{}
	public:
		bool can_contain(const sprite* const s) const override
		{
			MAGE_ASSERT(false, "Cannot update an n::sprite_batch");
			return false;
		}
		size_t add_tile(const n::sprite_bank& sb, const tile& t) override
		{
			MAGE_ASSERT(false, "Cannot update an n::sprite_batch");
			return 0;
		}
		void delete_tile(size_t offset)
		{
			MAGE_ASSERT(false, "Cannot update an n::sprite_batch");
		}
	};
}
