#pragma once
#include "pch.h"
#include "tile.h"
#include "n/graphics/wrap/buffer.h"
#include "n/graphics/wrap/shader_program.h"
#include "n/graphics/wrap/vertex_array.h"

namespace n
{
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
			m_texture_indices(other.m_texture_indices)
		{
			other.m_indices = nullptr;
			other.m_vertices = nullptr;
			other.m_vertex_array = nullptr;
		}
		virtual ~sprite_batch_base();
	public:
		virtual void save(mage::output_file& out) const override;
		virtual void load(mage::input_file& in) override;
		virtual void draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader)
		{
			draw_base(t, sb, ab, shader);
		}
		virtual bool can_contain(const sprite* const s) const = 0;
		virtual void add_tile(const tile& t) = 0;
	protected:
		mage::gfx::index_buffer* m_indices;
		mage::gfx::vertex_buffer* m_vertices;
		mage::gfx::vertex_array* m_vertex_array;
		std::unordered_map<sprite_atlas_bank::handle, size_t> m_atlases;
		std::vector<sprite_bank::handle> m_sprites;
		std::vector<glm::vec2> m_offsets;
		std::vector<int> m_texture_indices;
	protected:
		sprite_batch_base() :
			m_indices(nullptr),
			m_vertices(nullptr),
			m_vertex_array(nullptr)
		{}
	protected:
		void add_sprite(sprite_bank::handle sprite);
		template<typename SAB>
		void draw_base(const mage::timestep& t, sprite_bank* const sb, const SAB* const ab, const shader_program& shader)
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
	};



	class sprite_batch final : public sprite_batch_base
	{
	public:
		// static gl stuff
		sprite_batch(mage::input_file& in) { load(in); }
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
		void add_tile(const tile& t) override
		{
			MAGE_ASSERT(false, "Cannot update an n::sprite_batch");
		}
	};
}
