#pragma once
#include "pch.h"
#include "orc/graphics/sprite_atlas_bank.h"

namespace orc
{
	class sprite_atlas;
	class sprite_atlas_bank;
	class sprite_bank;

	class sprite final : public mage::sprite
	{
	public:
		sprite(sprite_bank* const sb, sprite_atlas_bank* const ab, const std::string& fp);
		sprite(coga::input_file& in) :
			mage::sprite(0)
		{
			load(in);
		}
		COGA_DCM(sprite);
	public:
		void save(coga::output_file& out) const override;
		void load(coga::input_file& in) override;
		const std::unordered_set<sprite_atlas_bank::handle>& get_atlases() const
		{
			return m_atlases;
		}
		s_type get_tile_w() const
		{
			return m_w / mage::c::pixels_per_sprite_side;
		}
		s_type get_tile_h() const
		{
			return m_h / mage::c::pixels_per_sprite_side;
		}
	private:
		std::unordered_set<sprite_atlas_bank::handle> m_atlases;
	private:
		bool add_to_atlas(sprite_atlas* const atlas, const uint8_t* const color_data, size_t i);
	};
}
