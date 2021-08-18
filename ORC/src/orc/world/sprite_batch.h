#pragma once
#include "pch.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class sprite;

	class sprite_batch final : public n::sprite_batch_base
	{
	public:
		sprite_batch(const glm::uvec2& base);
		sprite_batch(mage::input_file& in) :
			n::sprite_batch_base({ 0, 0 })
		{
			load(in);
		}
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			n::sprite_batch_base(std::move(other)),
			m_max_tile_count(other.m_max_tile_count),
			m_tile_count(other.m_tile_count),
			m_sprite_indices(std::move(other.m_sprite_indices)),
			m_openings(std::move(other.m_openings))
		{}
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		bool can_contain(const n::sprite* const s) const override;
		size_t add_tile(const n::tile& t) override;
		void delete_tile(size_t offset) override;
		void draw(const mage::timestep& t, n::sprite_bank* const sb, const sprite_atlas_bank* const ab, const n::shader_program& shader)
		{
			n::sprite_batch_base::draw(t, sb, ab, shader);
		}
		bool is_empty() const
		{
			return m_tile_count == m_openings.size();
		}
		// TODO
		//void remove(const tile& t);
	private:
		size_t m_max_tile_count, m_tile_count;
		std::unordered_map<n::sprite_bank::handle, size_t> m_sprite_indices;
		mutable std::vector<size_t> m_openings;
	private:
		void resize();
		void create_indices();
		void create_array();
		size_t get_next() const
		{
			size_t i = m_tile_count;
			if (!m_openings.empty())
			{
				i = m_openings.back();
				m_openings.pop_back();
			}
			return i;
		}
	};
}
