#pragma once
#include "pch.h"

namespace n
{
	class sprite;
	class sprite_atlas_bank;

	class sprite_bank final :
		public mage::bank<sprite, uint16_t, 65536>,
		public mage::serializable
	{
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
	};
}
