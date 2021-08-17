#pragma once
#include "pch.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class chunk;
	class sprite;

	class map final : public mage::serializable
	{
		typedef std::unordered_map<size_t, std::unordered_map<size_t, chunk*>> grid;
	public:
		map(sprite_atlas_bank* const atlases, n::sprite_bank* const sprites, const grid& chunks);
		map(mage::input_file& in)
		{
			load(in);
		}
		N_DCM(map);
		~map();
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		void draw(const mage::timestep& t, const n::shader_program& shader);
		void set_tile_at(const glm::uvec2& pos, size_t layer, sprite* const sprite);
	private:
		sprite_atlas_bank* m_atlases;
		n::sprite_bank* m_sprites;
		grid m_chunks;
	};
}
