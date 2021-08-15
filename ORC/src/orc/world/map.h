#pragma once
#include "pch.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class chunk;

	class map final : public mage::serializable
	{
	public:
		map(sprite_atlas_bank* const atlases, n::sprite_bank* const sprites, const std::vector<chunk*>& chunks);
		map(mage::input_file& in)
		{
			load(in);
		}
		N_DCM(map);
		~map();


		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
		void draw(const mage::timestep& t, const n::shader_program& shader);
	private:
		sprite_atlas_bank* m_atlases;
		n::sprite_bank* m_sprites;
		std::vector<chunk*> m_chunks;
	};
}
