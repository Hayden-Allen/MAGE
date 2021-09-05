#pragma once
#include "pch.h"
#include "sprite_batch_bank.h"
#include "orc/graphics/sprite_atlas_bank.h"
#include "orc/graphics/sprite_bank.h"
#include "orc/util/buildable.h"

namespace orc
{
	class chunk;
	class sprite;

	class map final :
		public mage::map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>,
		public buildable
	{
	public:
		map(sprite_atlas_bank* const atlases, sprite_bank* const sprites);
		map(coga::input_file& in)
		{
			load(in);
		}
		COGA_DCM(map);
		~map();
	public:
		void build(coga::output_file& out) const override;
		void save(coga::output_file& out) const override;
		void load(coga::input_file& in) override;
		void set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite);
		void delete_tile_at(const glm::uvec2& pos, size_t layer);
	private:
		sprite_batch_bank* m_batches;
	private:
		std::pair<glm::uvec2, glm::uvec2> find_root(const glm::uvec2& pos, size_t layer) const;
		void fill_grids(const glm::uvec2& pos, const glm::uvec2& dims, size_t layer, sprite_bank::handle h);
		bool can_set(const glm::uvec2& pos, size_t layer, const sprite* const sprite) const;
		chunk* const try_create_chunk(const glm::uvec2& pos);
		bool has_chunk(const glm::uvec2& pos) const
		{
			return m_chunks.contains(pos.y) && m_chunks.at(pos.y).contains(pos.x);
		}
	};
}
