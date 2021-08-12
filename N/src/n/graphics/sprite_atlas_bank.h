#pragma once
#include "pch.h"

namespace n
{
	class sprite_atlas;

	class sprite_atlas_bank final :
		public mage::bank<sprite_atlas, uint8_t, 256>,
		public mage::serializable
	{
	public:
		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
	};
}
