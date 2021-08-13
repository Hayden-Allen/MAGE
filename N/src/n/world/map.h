#pragma once
#include "pch.h"
#include "n/timestep.h"
#include "n/graphics/sprite_atlas_bank.h"
#include "n/graphics/sprite_bank.h"
#include "n/graphics/wrap/shader_program.h"

namespace n
{
	class chunk;

	class map final
	{
	public:
		map(sprite_atlas_bank* const atlases, sprite_bank* const sprites, const std::vector<chunk*>& chunks);
		N_DCM(map);
		~map();


		void draw(const timestep& t, const shader_program& shader);
	private:
		sprite_atlas_bank* m_atlases;
		sprite_bank* m_sprites;
		std::vector<chunk*> m_chunks;
	};
}
