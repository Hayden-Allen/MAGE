#pragma once
#include "pch.h"
#include "sprite_batch_bank.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite_atlas_bank.h"
#include "orc/graphics/sprite_bank.h"

namespace orc
{
	class sprite;

	class sprite_batch final : public mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>
	{
	public:
		sprite_batch(sprite_batch_bank& bank, const glm::uvec2& base);
		sprite_batch(coga::input_file& in) :
			mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>({ 0, 0 })
		{
			load(in);
		}
		MAGE_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>(std::move(other)),
			m_handle(other.m_handle),
			m_max_tile_count(other.m_max_tile_count),
			m_next_tile(other.m_next_tile),
			m_sprite_indices(std::move(other.m_sprite_indices)),
			m_sprite_counts(std::move(other.m_sprite_counts)),
			m_atlas_counts(std::move(other.m_atlas_counts)),
			m_openings(std::move(other.m_openings))
		{}
	public:
		void save(coga::output_file& out) const override;
		void load(coga::input_file& in) override;
		bool can_contain(const sprite* const s) const override;
		size_t add_tile(const sprite_bank& sb, const mage::tile& t) override;
		void delete_tile(const sprite* const s, size_t offset);
		void draw(const coga::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const mage::shader_program& shader)
		{
			mage::sprite_batch_base<mage::static_index_buffer, mage::retained_dynamic_vertex_buffer, mage::dynamic_vertex_array, sprite, sprite_bank>::draw(t, sb, ab, shader);
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
		// maps a sprite to its local index in this batch
		std::unordered_map<sprite_bank::handle, size_t> m_sprite_indices;
		std::unordered_map<sprite_bank::handle, size_t> m_sprite_counts;
		std::unordered_map<sprite_atlas_bank::handle, size_t> m_atlas_counts;
		mutable std::vector<size_t> m_openings;
	private:
		void resize();
		void create_indices();
		void create_array();
		size_t get_next() const;
		void add_sprite(sprite_bank::handle s) override;
		void remove_sprite(sprite_bank::handle s) override;
		void add_atlas(sprite_atlas_bank::handle atlas) override;
		void delete_tile(size_t offset) override;
	};
}
