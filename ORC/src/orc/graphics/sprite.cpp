#include "pch.h"
#include "sprite.h"
#include "sprite_atlas.h"

using namespace mage::game;

namespace orc
{
	sprite::sprite(sprite_bank* const sb, sprite_atlas_bank* const ab, const std::string& fp) :
		mage::game::sprite(sb)
	{
		input_file data(fp);

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
				// TODO
				bool result = add_to_atlas((sprite_atlas* const)atlas, color_data, i);
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
