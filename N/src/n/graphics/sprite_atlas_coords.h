#pragma once
#include "pch.h"

namespace n
{
	struct sprite_atlas_coords final : public mage::serializable
	{
		mage::range<float> x = { -1.f, 0.f }, y = { -1.f, 0.f };


		sprite_atlas_coords() {}
		sprite_atlas_coords(const mage::range<float>& _x, const mage::range<float>& _y)
		{
			x = _x;
			y = _y;
		}
		sprite_atlas_coords(const sprite_atlas_coords& other)
		{
			operator=(other);
		}


		void save(mage::output_file& out) const override
		{
			float min = x.get_min(), max = x.get_max();
			out.uint(MAGE_PUN(uint32_t, min)).uint(MAGE_PUN(uint32_t, max));
			min = y.get_min(); max = y.get_max();
			out.uint(MAGE_PUN(uint32_t, min)).uint(MAGE_PUN(uint32_t, max));
		}
		void load(mage::input_file& in) override
		{
			uint32_t min = in.uint(), max = in.uint();
			x = { MAGE_PUN(float, min), MAGE_PUN(float, max) };
			min = in.uint(); max = in.uint();
			y = { MAGE_PUN(float, min), MAGE_PUN(float, max) };
		}
		void operator=(const sprite_atlas_coords& other)
		{
			x = other.x;
			y = other.y;
		}
		bool operator==(const sprite_atlas_coords& other) const
		{
			return x == other.x && y == other.y;
		}
		glm::vec2 operator-(const sprite_atlas_coords& other) const
		{
			return { x.get_min() - other.x.get_min(), y.get_min() - other.y.get_min() };
		}
		bool is_invalid() const
		{
			return x == mage::range<float>(-1.f, 0.f) && y == mage::range<float>(-1.f, 0.f);
		}
	};
}
