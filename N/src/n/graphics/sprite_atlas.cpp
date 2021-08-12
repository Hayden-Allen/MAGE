#include "pch.h"
#include "sprite_atlas.h"
#include "sprite.h"

namespace n
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		mage::dimensional<uint32_t>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(bank->add(this)),
		m_texture(nullptr)
	{
		m_texture = new n::retained_texture2d(m_w, m_h, nullptr, m_w * m_h * c::bytes_per_pixel,
			{
				.min_filter = texture_min_filter::nearest,
				.mag_filter = texture_mag_filter::nearest,
				.wrap_s = texture_wrap_s::clamp_border,
				.wrap_t = texture_wrap_t::clamp_border
			}
		);
		m_x_step.insert(0);
		m_y_step.insert(0);
		m_starts.insert({ 0, 0, c::sprite_atlas_size, c::sprite_atlas_size });
	}



	void sprite_atlas::save(mage::output_file& out) const
	{
		// save texture
		m_texture->save(out);

		// save steps
		out.ulong(m_x_step.size()).ulong(m_y_step.size());
		for (s_type s : m_x_step)
			out.uint(s);
		for (s_type s : m_y_step)
			out.uint(s);

		// save rects
		out.ulong(m_starts.size()).ulong(m_used.size());
		for (const rect& r : m_starts)
			out.uint(r.min.x).uint(r.min.y).uint(r.max.x).uint(r.max.y);
		for (const rect& r : m_used)
			out.uint(r.min.x).uint(r.min.y).uint(r.max.x).uint(r.max.y);
	}
	void sprite_atlas::load(mage::input_file& in)
	{
		// load texture
		m_texture->load(in);

		// load steps
		size_t x_size = in.ulong(), y_size = in.ulong();
		for (size_t i = 0; i < x_size; i++)
			m_x_step.insert(in.uint());
		for (size_t i = 0; i < y_size; i++)
			m_y_step.insert(in.uint());

		// load rects
		size_t start_size = in.ulong(), used_size = in.ulong();
		for (size_t i = 0; i < start_size; i++)
			m_starts.insert({ { in.uint(), in.uint() }, { in.uint(), in.uint() } });
	}
	sprite_atlas_coords sprite_atlas::insert(s_type w, s_type h, const uint8_t* const data)
	{
		for (const rect& r : m_starts)
			if (r.get_w() >= w && r.get_h() >= h)
				return insert({ w, h }, r, data);

		// given rect doesn't fit in this atlas
		return {};
	}



	sprite_atlas_coords sprite_atlas::insert(const point& dims, const rect& spot, const uint8_t* const data)
	{
		// bounds of new rect
		const s_type x_start = spot.min.x, x_end = spot.min.x + dims.x;
		const s_type y_start = spot.min.y, y_end = spot.min.y + dims.y;
		// insert new steps
		m_x_step.insert(x_end);
		m_y_step.insert(y_end);
		// insert edges as steps to calculate the max area rectangle that can be formed at each point
		m_x_step.insert(c::sprite_atlas_size);
		m_y_step.insert(c::sprite_atlas_size);

		// insert new rect
		m_texture->update(x_start, y_start, dims.x, dims.y, data);
		m_used.insert({ spot.min, { x_end, y_end } });

		// account for new rect
		update();
		/*MAGE_INFO("UPDATE");
		for (auto& r : m_starts)
			MAGE_INFO("[<{}, {}>, <{}, {}>] => {}", r.min.x, r.min.y, r.max.x, r.max.y, r.get_area());*/

		// normalized texture coordinates of new rect
		return { { 1.f * x_start / c::sprite_atlas_size, 1.f * x_end / c::sprite_atlas_size }, { 1.f * y_start / c::sprite_atlas_size, 1.f * y_end / c::sprite_atlas_size } };
	}
	void sprite_atlas::update()
	{
		// set of fewest possible rectangles, each having the largest possible area, such that all unused space left in the texture is covered by the union of the set
		std::vector<rect> rects = gen_rects(gen_points());

		// reset internal state
		m_starts.clear();
		m_x_step.clear();
		m_y_step.clear();
		for (const rect& r : rects)
		{
			m_starts.insert(r);
			m_x_step.insert(r.min.x);
			m_y_step.insert(r.min.y);
		}
	}
	std::vector<sprite_atlas::point> sprite_atlas::gen_points() const
	{
		std::vector<point> points;
		for (s_type x : m_x_step)
		{
			for (s_type y : m_y_step)
			{
				point p = { x, y };
				bool contained = false;
				for (const rect& r : m_used)
					if (contained = r.contains(p, s_contains))
						break;
				if (!contained)
					points.push_back(p);
			}
		}
		return points;
	}
	std::vector<sprite_atlas::rect> sprite_atlas::gen_rects(const std::vector<point>& points) const
	{
		size_t index = 0;
		std::unordered_set<rect, rect_hash> possible;
		for (const point& p : points)
		{
			rect cur = { p, p };
			for (const point& q : points)
			{
				const point min = { glm::min(p.x, q.x), glm::min(p.y, q.y) };
				const point max = { glm::max(p.x, q.x), glm::max(p.y, q.y) };
				rect test = { min, max };

				if (test.get_area() <= cur.get_area())
					continue;

				bool intersects = false;
				for (const rect& r : m_used)
				{
					intersects = test.intersects(r, (test.contains(r, s_overlaps_inc) ? s_overlaps_inc : s_overlaps_exc));
					/*MAGE_INFO("[<{}, {}>, <{}, {}>] vs [<{}, {}>, <{}, {}>] => {}", test.min.x, test.min.y, test.max.x, test.max.y, r.min.x, r.min.y, r.max.x, r.max.y, intersects);*/
					if (intersects)
						break;
				}

				if (!intersects)
					cur = test;
			}
			if(cur.get_area() > 0)
				possible.insert(cur);
		}
		/*MAGE_INFO("POSSIBLE");
		for (auto& r : possible)
			MAGE_INFO("[<{}, {}>, <{}, {}>]", r.min.x, r.min.y, r.max.x, r.max.y);*/

		std::vector<rect> result;
		for (const rect& a : possible)
		{
			bool contained = false;
			for (const rect& b : possible)
				if (a != b && (contained = b.contains(a, s_overlaps_inc)))
					break;
			if (!contained)
				result.push_back(a);
		}
		return result;
	}
}
