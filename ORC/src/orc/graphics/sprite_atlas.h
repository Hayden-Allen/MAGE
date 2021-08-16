#pragma once
#include "pch.h"

namespace orc
{
	class sprite_atlas_bank;

	class sprite_atlas final :
		public n::sprite_atlas,
		public mage::rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>
	{
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		sprite_atlas(mage::input_file& in);
		MAGE_DCM(sprite_atlas);
	public:
		n::sprite_atlas_coords insert(uint32_t w, uint32_t h, const uint8_t* const data)
		{
			return mage::rect_packer<uint32_t, n::sprite_atlas_coords, uint8_t>::insert(w, h, data);
		}
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
	private:
		n::sprite_atlas_coords insert(const point& dims, const rect& spot, const uint8_t* const data) override;
	};
}
