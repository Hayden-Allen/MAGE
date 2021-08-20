#pragma once
#include "pch.h"
#include "sprite_batch_bank.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite_atlas_bank.h"
#include "orc/graphics/sprite_bank.h"

namespace orc
{
	class sprite;

	class sprite_batch final : public n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>
	{
	public:
		sprite_batch(sprite_batch_bank& bank, const glm::uvec2& base);
		sprite_batch(mage::input_file& in) :
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>({ 0, 0 })
		{
			load(in);
		}
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>(std::move(other)),
			m_handle(other.m_handle),
			m_max_tile_count(other.m_max_tile_count),
			m_next_tile(other.m_next_tile),
			m_sprite_indices(std::move(other.m_sprite_indices)),
			m_sprite_counts(std::move(other.m_sprite_counts)),
			m_atlas_counts(std::move(other.m_atlas_counts)),
			m_openings(std::move(other.m_openings))
		{}
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		bool can_contain(const sprite* const s) const override;
		size_t add_tile(const sprite_bank& sb, const n::tile& t) override;
		void delete_tile(const sprite* const s, size_t offset);
		void draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const n::shader_program& shader)
		{
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::draw(t, sb, ab, shader);
		}
		bool is_empty() const
		{
			return m_next_tile == m_openings.size();
		}
		bool is_full() const
		{
			return m_openings.empty() && m_next_tile == m_max_tile_count;
		}
		sprite_batch_bank::handle get_handle() const
		{
			return m_handle;
		}
	private:
		sprite_batch_bank::handle m_handle;
		size_t m_max_tile_count, m_next_tile;
		// maps a sprite_bank to its local index in this batch
		std::unordered_map<sprite_bank::handle, size_t> m_sprite_indices;
		std::unordered_map<sprite_bank::handle, size_t> m_sprite_counts;
		std::unordered_map<sprite_atlas_bank::handle, size_t> m_atlas_counts;
		mutable std::vector<size_t> m_openings;
	private:
		void resize();
		void create_indices();
		void create_array();
		size_t get_next() const
		{
			size_t i = m_next_tile;
			if (!m_openings.empty())
			{
				i = m_openings.back();
				m_openings.pop_back();
			}
			return i;
		}
		void add_sprite(sprite_bank::handle s) override
		{
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::add_sprite(s);
			if (!m_sprite_counts.contains(s))
				m_sprite_counts.insert({ s, 0 });
			m_sprite_counts[s]++;
		}
		void remove_sprite(sprite_bank::handle s) override
		{
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::remove_sprite(s);

			auto& ref = m_sprite_counts[s];
			ref--;
			if (ref == 0)
				m_sprite_counts.erase(s);
		}
		void add_atlas(sprite_atlas_bank::handle atlas) override
		{
			n::sprite_batch_base<n::static_index_buffer, n::retained_dynamic_vertex_buffer, n::dynamic_vertex_array, sprite, sprite_bank>::add_atlas(atlas);

			if (!m_atlas_counts.contains(atlas))
				m_atlas_counts.insert({ atlas, 0 });
			m_atlas_counts[atlas]++;
		}
		void delete_tile(size_t offset) override
		{
			float vertices[n::c::floats_per_tile] = { 0.f };
			m_vertices->update(vertices, n::c::floats_per_tile, offset);
			m_openings.push_back(offset / n::c::floats_per_tile);
		}
	};
}
