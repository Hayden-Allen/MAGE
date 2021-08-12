#pragma once
#include "pch.h"
#include "sprite_atlas_bank.h"
#include "sprite_atlas_coords.h"
#include "wrap/texture.h"

namespace n
{



	class sprite_atlas final :
		public mage::dimensional<uint32_t>,
		public mage::serializable
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
		sprite_atlas(mage::input_file& in);
		MAGE_DCM(sprite_atlas);
		~sprite_atlas()
		{
			delete m_texture;
		}


		void save(mage::output_file& out) const override;
		void load(mage::input_file& in) override;
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
		constexpr static texture_options s_texture_options = { .min_filter = texture_min_filter::nearest, .mag_filter = texture_mag_filter::nearest, .wrap_s = texture_wrap_s::clamp_border, .wrap_t = texture_wrap_t::clamp_border };


		sprite_atlas_bank::handle m_handle;
		retained_texture2d* m_texture;
		std::set<s_type> m_x_step, m_y_step;
		std::multiset<rect, rect_area_comparator> m_starts, m_used;


		sprite_atlas_coords insert(const point& dims, const rect& spot, const uint8_t* const data);
		void update();
		std::vector<point> gen_points() const;
		std::vector<rect> gen_rects(const std::vector<point>& points) const;
	};
}
