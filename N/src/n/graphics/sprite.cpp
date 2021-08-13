#include "pch.h"
#include "sprite.h"

namespace n
{
	sprite::sprite(sprite_bank* const sb, sprite_atlas_bank* const ab, const std::string& fp) :
		mage::dimensional<uint8_t>(0, 0),
		m_handle(sb->add(this)),
		m_frame(0),
		m_frame_count(0),
		m_frame_time(0),
		m_base_coords({ 0.f, 1.f }, { 0.f, 1.f })
	{
		mage::input_file data(fp);

		// info
		m_w = data.ubyte() * c::pixels_per_sprite_side;
		m_h = data.ubyte() * c::pixels_per_sprite_side;
		m_frame_count = data.ubyte();
		MAGE_ASSERT(m_frame_count <= c::max_sprite_frame_count, "Sprites cannot have more than {} frames", c::max_sprite_frame_count);
		m_frame_time = data.ushort();

		// palette
		uint8_t r[c::sprite_color_count], g[c::sprite_color_count], b[c::sprite_color_count];
		for (int i = 0; i < c::sprite_color_count; i++)
		{
			r[i] = data.ubyte();
			g[i] = data.ubyte();
			b[i] = data.ubyte();
		}

		// generate color data from palette indices
		const size_t pixels_per_frame = m_w * m_h;
		uint8_t* const color_data = new uint8_t[c::bytes_per_sprite_pixel * pixels_per_frame * m_frame_count];
		for (size_t i = 0; i < m_frame_count; i++)
		{
			// base address of current frame
			const size_t off = i * pixels_per_frame * c::bytes_per_sprite_pixel;
			for (size_t j = 0; j < pixels_per_frame * c::bytes_per_sprite_pixel; j += c::bytes_per_sprite_pixel)
			{
				// coordinates of current pixel
				// flip y because OpenGL expects data from the bottom up
				const size_t x = (j / c::bytes_per_sprite_pixel) % m_w;
				const size_t y = (m_h - 1) - (j / c::bytes_per_sprite_pixel) / m_w;
				const size_t index = off + (y * c::pixels_per_sprite_side + x) * c::bytes_per_sprite_pixel;
				// palette index of current pixel. 16 signifies empty
				const uint8_t color = data.ubyte();
				color_data[index + 0] = (color == c::sprite_color_count ? 0 : r[color]);
				color_data[index + 1] = (color == c::sprite_color_count ? 0 : g[color]);
				color_data[index + 2] = (color == c::sprite_color_count ? 0 : b[color]);
				color_data[index + 3] = (color == c::sprite_color_count ? 0 : 255);
			}
		}


		m_frame_data.reserve(m_frame_count);
		// current atlas index. Because all frames are the same size, we don't need to try inserting every frame into every atlas; if one frame doesn't fit, the rest won't either.
		sprite_atlas_bank::handle handle = 0;
		for (size_t i = 0; i < m_frame_count; i++)
		{
			// attempt to add current frame to remaining existing atlases
			bool added = false;
			while (!added && handle < ab->get_size())
			{
				const auto& atlas = ab->get(handle);
				bool result = add_to_atlas(atlas, color_data, i);
				// unable to add to current atlas, go to the next one
				if (!result)
				{
					handle++;
					continue;
				}
				// add successful, move to the next frame
				added = true;
			}
			// no room in existing atlases, need to make a new one
			if (!added)
				add_to_atlas(new sprite_atlas(ab), color_data, i);
		}
		delete[] color_data;
	}
	sprite::sprite(mage::input_file& in) :
		mage::dimensional<uint8_t>(0, 0),
		m_frame(0),
		m_frame_count(0),
		m_frame_time(0),
		m_base_coords({ 0.f, 1.f }, { 0.f, 1.f })
	{
		load(in);
	}



	void sprite::save(mage::output_file& out) const
	{
		out.uint(m_w).uint(m_h);
		out.ubyte(m_frame_count).ushort(m_frame_time);
		m_base_coords.save(out);
		for (uint8_t i = 0; i < m_frame_count; i++)
			m_frame_data[i].save(out);
	}
	void sprite::load(mage::input_file& in)
	{
		m_w = in.uint();
		m_h = in.uint();
		m_frame_count = in.ubyte();
		m_frame_time = in.ushort();
		m_base_coords.load(in);

		m_frame_data.reserve(m_frame_count);
		for (uint8_t i = 0; i < m_frame_count; i++)
		{
			frame_handle h;
			h.load(in);
			m_frame_data.push_back(h);
		}
	}
	void sprite::update(const timestep& t)
	{
		// if this sprite has multiple frames and enough time has passed, advance the frame
		if (m_frame_count > 1 && t - m_last_switch >= m_frame_time)
		{
			m_frame = (m_frame + 1) % m_frame_count;
			m_last_switch = t;
		}
	}



	bool sprite::add_to_atlas(sprite_atlas* const atlas, const uint8_t* const color_data, size_t i)
	{
		// attempt to add
		const auto& c = atlas->insert(m_w, m_h, color_data + i * m_w * m_h * c::bytes_per_sprite_pixel);
		// given atlas doesn't have room for this sprite
		if (c.is_invalid())
			return false;

		m_atlases.insert(atlas->get_handle());
		// first frame
		if (i == 0)
			m_base_coords = c;
		// for all frames, store delta between base coords and returned coords
		m_frame_data.push_back(frame_handle(atlas->get_handle(), c - m_base_coords));
		return true;
	}
}
