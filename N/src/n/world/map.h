#pragma once
#include "pch.h"
#include "n/graphics/wrap/shader_program.h"

namespace n
{
	class chunk;

	class map final
	{
	public:
		map(mage::game::sprite_atlas_bank* const atlases, mage::game::sprite_bank* const sprites, const std::vector<chunk*>& chunks);
		N_DCM(map);
		~map();


		void draw(const mage::timestep& t, const shader_program& shader);
	private:
		mage::game::sprite_atlas_bank* m_atlases;
		mage::game::sprite_bank* m_sprites;
		std::vector<chunk*> m_chunks;
	};
}
