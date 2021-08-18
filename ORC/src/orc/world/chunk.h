#pragma once
#include "pch.h"
#include "tile.h"
#include "sprite_batch.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class chunk final : public n::chunk
	{
	public:
		// chunk(const std::vector<tile>& tiles);
		chunk(const glm::uvec2& pos);
		chunk(mage::input_file& in);
		N_DCM(chunk);
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		void set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite);
		void delete_tile_at(const glm::uvec2& pos, size_t layer);
		bool is_empty() const
		{
			return m_tile_count == 0;
		}
		void draw(const mage::timestep& t, n::sprite_bank* const sb, const sprite_atlas_bank* const ab, const n::shader_program& shader)
		{
			for (auto& batch : m_batches)
				((sprite_batch*)batch)->draw(t, sb, ab, shader);
		}
	private:
		size_t m_tile_count;
		n::sprite_bank::handle m_grid[n::c::tiles_per_chunk];
		std::unordered_map<size_t, std::unordered_map<size_t, std::pair<n::sprite_batch_base*, size_t>>> m_tile_offsets;
	private:
		void draw(const mage::timestep& t, n::sprite_bank* const sb, const n::sprite_atlas_bank* const ab, const n::shader_program& shader) override
		{
			MAGE_ASSERT(false, "Cannot draw an orc::chunk with an n::sprite_atlas_bank");
		}
	};
}
