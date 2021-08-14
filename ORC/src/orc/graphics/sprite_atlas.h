#pragma once
#include "pch.h"

namespace orc
{
	class sprite_atlas final :
		public game::sprite_atlas,
		public rect_packer<uint32_t, game::sprite_atlas_coords, uint8_t>
	{
		using game::sprite_atlas::m_w;
		using game::sprite_atlas::m_h;
	public:
		sprite_atlas(game::sprite_atlas_bank* const bank);
		sprite_atlas(input_file& in);
		MAGE_DCM(sprite_atlas);


		game::sprite_atlas_coords insert(uint32_t w, uint32_t h, const uint8_t* const data)
		{
			return rect_packer<uint32_t, game::sprite_atlas_coords, uint8_t>::insert(w, h, data);
		}
		void save(output_file& out) const override;
		void load(input_file& in) override;
	private:
		game::sprite_atlas_coords insert(const point& dims, const rect& spot, const uint8_t* const data) override;
	};
}
