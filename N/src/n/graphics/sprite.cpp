#include "pch.h"
#include "sprite.h"
#include "n/io/file.h"

namespace n
{
	sprite::sprite(sprite_atlas* const atlas, const std::string& fp) :
		mage::dimensional<uint8_t>(0, 0),
		m_frame(0),
		m_frame_count(0),
		m_frame_time(0)
	{
		input_file data(fp);

		// info
		m_w = data.get_byte() * c::pixels_per_side;
		m_h = data.get_byte() * c::pixels_per_side;
		m_frame_count = data.get_byte();
		MAGE_ASSERT(m_frame_count <= c::max_frame_count, "Sprites cannot have more than {} frames", c::max_frame_count);
		m_frame_time = data.get_short();

		// palette
		uint8_t r[c::color_count], g[c::color_count], b[c::color_count];
		for (int i = 0; i < c::color_count; i++)
		{
			r[i] = data.get_byte();
			g[i] = data.get_byte();
			b[i] = data.get_byte();
		}

		// generate color data from palette indices
		const uint32_t pixels_per_frame = m_w * m_h;
		uint8_t* color_data = new uint8_t[c::bytes_per_pixel * pixels_per_frame * m_frame_count];
		for (size_t i = 0; i < m_frame_count; i++)
		{
			// base address of current frame
			const size_t off = i * pixels_per_frame * 4;
			for (size_t j = 0; j < pixels_per_frame * 4; j += 4)
			{
				// coordinates of current pixel
				// flip y because OpenGL expects data from the bottom up
				const size_t x = (j / 4) % m_w;
				const size_t y = (m_h - 1) - (j / 4) / m_w;
				const size_t index = off + (y * c::pixels_per_side + x) * 4;
				// palette index of current pixel. 16 signifies empty
				const uint8_t color = data.get_byte();
				color_data[index + 0] = (color == c::pixels_per_side ? 0 : r[color]);
				color_data[index + 1] = (color == c::pixels_per_side ? 0 : g[color]);
				color_data[index + 2] = (color == c::pixels_per_side ? 0 : b[color]);
				color_data[index + 3] = (color == c::pixels_per_side ? 0 : 255);
			}
		}

		//// upload color data to GPU
		//m_texture = new texture2d_array(m_w, m_h, m_frame_count, color_data,
		//	{
		//		.min_filter = texture_min_filter::nearest,
		//		.mag_filter = texture_mag_filter::nearest,
		//		.wrap_s = texture_wrap_s::clamp_border,
		//		.wrap_t = texture_wrap_t::clamp_border
		//	}
		//);
		m_coords = atlas->insert(m_w, m_h, m_frame_count, color_data);
		MAGE_INFO("<{}, {}> <{}, {}>", m_coords.x.get_min(), m_coords.x.get_max(), m_coords.y.get_min(), m_coords.y.get_max());
		delete[] color_data;
	}
}
