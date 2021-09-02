#pragma once
#include "pch.h"

namespace mage
{
	/**
	 * Texture coordinate data within a sprite atlas
	 */
	struct sprite_atlas_coords final : public coga::serializable
	{
		// initialize to invalid values
		coga::range<float> x = { -1.f, 0.f }, y = { -1.f, 0.f };


		sprite_atlas_coords() {}
		sprite_atlas_coords(const coga::range<float>& _x, const coga::range<float>& _y)
		{
			x = _x;
			y = _y;
		}
		sprite_atlas_coords(const sprite_atlas_coords& other)
		{
			operator=(other);
		}


		void save(coga::output_file& out) const override
		{
			float min = x.get_min(), max = x.get_max();
			out.uint(COGA_PUN(uint32_t, min)).uint(COGA_PUN(uint32_t, max));
			min = y.get_min(); max = y.get_max();
			out.uint(COGA_PUN(uint32_t, min)).uint(COGA_PUN(uint32_t, max));
		}
		void load(coga::input_file& in) override
		{
			uint32_t min = in.uint(), max = in.uint();
			x = { COGA_PUN(float, min), COGA_PUN(float, max) };
			min = in.uint(); max = in.uint();
			y = { COGA_PUN(float, min), COGA_PUN(float, max) };
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
		/**
		 * compute positional difference between two pairs of coords
		 */
		glm::vec2 operator-(const sprite_atlas_coords& other) const
		{
			COGA_ASSERT(x.get_span() == other.x.get_span() && y.get_span() == other.y.get_span(), "Cannot subtract sprite_atlas_coords of different dimensions");
			return { x.get_min() - other.x.get_min(), y.get_min() - other.y.get_min() };
		}
		bool is_invalid() const
		{
			return x == coga::range<float>(-1.f, 0.f) && y == coga::range<float>(-1.f, 0.f);
		}
	};
}
