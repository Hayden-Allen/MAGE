#pragma once
#include "pch.h"

namespace orc
{
	class sprite_atlas;

	class sprite final : public game::sprite
	{
	public:
		sprite(game::sprite_bank* const sb, game::sprite_atlas_bank* const ab, const std::string& fp);
		sprite(input_file& in);
		MAGE_DCM(sprite);


		const std::unordered_set<game::sprite_atlas_bank::handle>& get_atlases() const
		{
			return m_atlases;
		}
	private:
		std::unordered_set<game::sprite_atlas_bank::handle> m_atlases;


		bool add_to_atlas(sprite_atlas* const atlas, const uint8_t* const color_data, size_t i);
	};
}
