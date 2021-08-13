#include "pch.h"
#include "sprite_atlas.h"
#include "sprite.h"

namespace n
{
	sprite_atlas::sprite_atlas(sprite_atlas_bank* const bank) :
		mage::dimensional<uint32_t>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(bank->add(this)),
		m_texture(nullptr),
		m_x_max(0),
		m_y_max(0)
	{
		m_texture = new n::retained_texture2d(m_w, m_h, c::bytes_per_sprite_pixel * m_w * m_h, nullptr, s_texture_options);
		// start inserting at the origin
		m_x_step.insert(0);
		m_y_step.insert(0);
		// the whole texture is available
		m_starts.insert({ 0, 0, c::sprite_atlas_size, c::sprite_atlas_size });
	}
	sprite_atlas::sprite_atlas(mage::input_file& in) :
		mage::dimensional<uint32_t>(c::sprite_atlas_size, c::sprite_atlas_size),
		m_handle(0),
		m_texture(new retained_texture2d(m_w, m_h, c::bytes_per_sprite_pixel* m_w * m_h, s_texture_options)),
		m_x_max(0),
		m_y_max(0)
	{
		load(in);
	}



	void sprite_atlas::save(mage::output_file& out) const
	{
		// save index in bank
		out.ushort(m_handle);

		// save texture
		m_texture->save(out, 0, 0, m_x_max, m_y_max);

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
		// load index in bank
		m_handle = in.ushort();

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
		for (size_t i = 0; i < used_size; i++)
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
		m_x_max = glm::max(m_x_max, x_end);
		m_y_max = glm::max(m_y_max, y_end);
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
		// generate all possible points of interest
		for (s_type x : m_x_step)
		{
			for (s_type y : m_y_step)
			{
				point p = { x, y };
				// if the current point is within an existing rectangle, ignore it
				bool contained = false;
				for (const rect& r : m_used)
					if (contained = r.contains(p, s_contains_exc))
						break;
				if (!contained)
					points.push_back(p);
			}
		}
		return points;
	}
	std::vector<sprite_atlas::rect> sprite_atlas::gen_rects(const std::vector<point>& points) const
	{
		// given points of interest, generate rects between every pair of points
		size_t index = 0;
		std::unordered_set<rect, rect_hash> possible;
		for (const point& p : points)
		{
			// cache the largest rect so far
			rect cur = { p, p };
			for (const point& q : points)
			{
				// create a rect between p and q (swap things around so that min remains the top-left corner and max remains the bottom-right corner)
				const point min = { glm::min(p.x, q.x), glm::min(p.y, q.y) };
				const point max = { glm::max(p.x, q.x), glm::max(p.y, q.y) };
				rect test = { min, max };

				// if p == q or this rect is smaller than the cached one
				if (test.get_area() == 0 || test.get_area() <= cur.get_area())
					continue;

				// if this rect intersects any used space, ignore it
				bool intersects = false;
				for (const rect& r : m_used)
				{
					intersects = test.intersects(r, (test.contains(r, s_overlaps_inc) ? s_overlaps_inc : s_overlaps_exc));
					/*MAGE_INFO("[<{}, {}>, <{}, {}>] vs [<{}, {}>, <{}, {}>] => {}", test.min.x, test.min.y, test.max.x, test.max.y, r.min.x, r.min.y, r.max.x, r.max.y, intersects);*/
					if (intersects)
						break;
				}

				// otherwise, this is the largest rect so far
				if (!intersects)
					cur = test;
			}
			if(cur.get_area() > 0)
				possible.insert(cur);
		}
		/*MAGE_INFO("POSSIBLE");
		for (auto& r : possible)
			MAGE_INFO("[<{}, {}>, <{}, {}>]", r.min.x, r.min.y, r.max.x, r.max.y);*/

		// filter generated rects such that the smallest list of rects that cover the same area remain; remove any rects that are inside other rects
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
