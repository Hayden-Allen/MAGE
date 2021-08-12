#pragma once
#include "pch.h"
#include "sprite_atlas_bank.h"
#include "wrap/texture.h"

namespace n
{
	struct sprite_atlas_coords final
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



	class sprite_atlas final : public mage::dimensional<uint32_t>
	{
		using point = mage::point<s_type>;
		using rect = mage::rect<s_type>;

		// hopefully this is good enough
		struct rect_hash
		{
			size_t operator()(const rect& r) const
			{
				const auto temp = std::hash<s_type>();
				return temp(r.min.x) ^ temp(r.max.x) ^ (r.min.y) ^ (r.max.y);
			}
		};
		struct rect_area_comparator
		{
			bool operator()(const rect& a, const rect& b) const
			{
				return a.get_area() > b.get_area();
			}
		};
	public:
		sprite_atlas(sprite_atlas_bank* const bank);
		MAGE_DCM(sprite_atlas);
		~sprite_atlas()
		{
			delete m_texture;
		}


		sprite_atlas_coords insert(s_type w, s_type h, const uint8_t* const data);
		void bind(uint32_t slot) const
		{
			m_texture->bind(slot);
		}
		sprite_atlas_bank::handle get_handle() const
		{
			return m_handle;
		}
	private:
		constexpr static mage::range_contains s_contains = { false, false };
		constexpr static mage::range_overlaps s_overlaps_inc = { { true, true }, { true, true } };
		constexpr static mage::range_overlaps s_overlaps_exc = { { false, false }, { false, false } };


		sprite_atlas_bank::handle m_handle;
		texture2d* m_texture;
		std::set<s_type> m_x_step, m_y_step;
		std::multiset<rect, rect_area_comparator> m_starts, m_used;


		sprite_atlas_coords insert(const point& dims, const rect& spot, const uint8_t* const data);
		void update();
		std::vector<point> gen_points() const;
		std::vector<rect> gen_rects(const std::vector<point>& points) const;
	};
}
