#include "pch.h"
#include "sprite.h"
#include "n/io/file.h"

namespace n
{
	sprite::sprite(const std::string& fp) :
		mage::dimensional<uint8_t>(0, 0),
		m_frame(0),
		m_frame_count(0),
		m_frame_time(0),
		m_texture(nullptr)
	{
		input_file data(fp);

		m_w = data.get_byte();
		m_h = data.get_byte();
		m_frame_count = data.get_byte();
		m_frame_time = data.get_short();
		MAGE_INFO("{} {} {} {}", m_w, m_h, m_frame_count, m_frame_time);

		uint8_t r[s_color_count], g[s_color_count], b[s_color_count];
		for (int i = 0; i < s_color_count; i++)
		{
			r[i] = data.get_byte();
			g[i] = data.get_byte();
			b[i] = data.get_byte();
		}
		mage::arrprint(r, "%u", ", ", 4);
		mage::arrprint(g, "%u", ", ", 4);
		mage::arrprint(b, "%u", ", ", 4);

		const size_t pixels_per_frame = s_pixels_per_tile * m_w * m_h;
		uint8_t* color_data = new uint8_t[4 * pixels_per_frame * m_frame_count];

		for (int i = 0; i < m_frame_count; i++)
		{
			const size_t off = i * pixels_per_frame * 4;
			for (int j = 0; j < pixels_per_frame * 4; j += 4)
			{
				uint8_t index = data.get_byte();
				color_data[off + j + 0] = (index == s_pixels_per_side ? 0 : r[index]);
				color_data[off + j + 1] = (index == s_pixels_per_side ? 0 : g[index]);
				color_data[off + j + 2] = (index == s_pixels_per_side ? 0 : b[index]);
				color_data[off + j + 3] = (index == s_pixels_per_side ? 0 : 255);
			}
		}
		mage::arrprint(4 * pixels_per_frame * m_frame_count, color_data, "%u", ", ", 16);

		m_texture = new texture2d_array(m_w * s_pixels_per_side, m_h * s_pixels_per_side, m_frame_count, color_data,
			{
				.min_filter = texture_min_filter::nearest,
				.mag_filter = texture_mag_filter::nearest,
				.wrap_s = texture_wrap_s::clamp_border,
				.wrap_t = texture_wrap_t::clamp_border,
				.target_format = texture_target_format::rgba8,
				.source_format = texture_source_format::rgba,
				.source_type = texture_source_type::byte
			}
		);

		delete[] color_data;
	}
}
