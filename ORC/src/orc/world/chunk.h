#pragma once
#include "pch.h"
#include "sprite_batch.h"
#include "sprite_batch_bank.h"
#include "orc/graphics/sprite_atlas_bank.h"
#include "orc/util/buildable.h"

namespace orc
{
	class chunk final :
		public mage::chunk_base<sprite_batch>,
		public buildable
	{
		friend class map;
	public:
		chunk(const glm::uvec2& pos);
		chunk(sprite_batch_bank& sbb, coga::input_file& in);
		COGA_DCM(chunk);
	public:
		void build(coga::output_file& out) const override;
		void save(coga::output_file& out) const override;
		void load(sprite_batch_bank& sbb, coga::input_file& in);
		void set_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer, const sprite* const sprite);
		void delete_tile_at(sprite_batch_bank& sbb, const sprite_bank& sb, const glm::uvec2& pos, size_t layer);
		sprite_bank::handle get_tile_at(const glm::uvec2& pos, size_t layer) const;
		bool is_empty() const
		{
			return m_tile_count == 0;
		}
		void draw(const coga::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const mage::shader_program& shader)
		{
			mage::chunk_base<sprite_batch>::draw(t, sb, ab, shader);
		}
	private:
		size_t m_tile_count;
		mage::sprite_bank::handle m_grid[mage::c::tiles_per_chunk];
		// layer, y, x, <handle, offset>
		std::unordered_map<size_t, std::unordered_map<size_t, std::unordered_map<size_t, std::pair<sprite_batch_bank::handle, size_t>>>> m_tile_offsets;
	private:
		static size_t get_index(const glm::uvec2& pos, size_t layer);
		// void fill_grid(const glm::uvec2& pos, const glm::uvec2& dim, size_t layer, sprite_bank::handle h);
		void load(coga::input_file& in) override
		{
			mage::chunk_base<sprite_batch>::load(in);
		}
	};
}
