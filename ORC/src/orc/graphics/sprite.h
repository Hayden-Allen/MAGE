#pragma once
#include "pch.h"

namespace orc
{
	class sprite_atlas;
	class sprite_atlas_bank;

	class sprite final : public n::sprite
	{
	public:
		sprite(n::sprite_bank* const sb, sprite_atlas_bank* const ab, const std::string& fp);
		sprite(mage::input_file& in);
		MAGE_DCM(sprite);
	public:
		const std::unordered_set<n::sprite_atlas_bank::handle>& get_atlases() const
		{
			return m_atlases;
		}
	private:
		std::unordered_set<n::sprite_atlas_bank::handle> m_atlases;
	private:
		bool add_to_atlas(sprite_atlas* const atlas, const uint8_t* const color_data, size_t i);
	};
}