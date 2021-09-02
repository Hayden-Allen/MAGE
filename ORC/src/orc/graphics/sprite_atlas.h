#pragma once
#include "pch.h"

namespace orc
{
	class sprite_atlas_bank;

	class sprite_atlas final :
		public mage::sprite_atlas,
		public coga::rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>
	{
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		sprite_atlas(coga::input_file& in);
		COGA_DCM(sprite_atlas);
	public:
		void save(coga::output_file& out) const override;
		void load(coga::input_file& in) override;
		mage::sprite_atlas_coords insert(uint32_t w, uint32_t h, const uint8_t* const data)
		{
			return coga::rect_packer<uint32_t, mage::sprite_atlas_coords, uint8_t>::insert(w, h, data);
		}
	private:
		mage::sprite_atlas_coords insert(const point& dims, const rect& spot, const uint8_t* const data) override;
	};
}
