#pragma once
#include "pch.h"
#include "sprite_batch.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class chunk final : public n::chunk_base<sprite_batch>
	{
	public:
		// chunk(const std::vector<tile>& tiles);
		chunk(const glm::uvec2& pos);
		chunk(mage::input_file& in);
		N_DCM(chunk);
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		void set_tile_at(const sprite_bank& sb, const glm::uvec2& pos, size_t layer, sprite* const sprite);
		void delete_tile_at(const glm::uvec2& pos, size_t layer);
		bool is_empty() const
		{
			return m_tile_count == 0;
		}
		void draw(const mage::timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const n::shader_program& shader)
		{
			n::chunk_base<sprite_batch>::draw(t, sb, ab, shader);
		}
	private:
		size_t m_tile_count;
		n::sprite_bank::handle m_grid[n::c::tiles_per_chunk];
		std::unordered_map<size_t, std::unordered_map<size_t, std::pair<sprite_batch*, size_t>>> m_tile_offsets;
	private:
		size_t get_index(const glm::uvec2& pos, size_t layer) const
		{
			MAGE_ASSERT(pos.x < n::c::tiles_per_chunk_side&& pos.y < n::c::tiles_per_chunk_side, "Invalid chunk coordinates <{}, {}>", pos.x, pos.y);
			MAGE_ASSERT(layer < n::c::layers_per_chunk, "Invalid chunk layer {}", layer);

			return (layer * n::c::tiles_per_chunk_layer) + (pos.y * n::c::tiles_per_chunk_side) + pos.x;
		}
	};
}
