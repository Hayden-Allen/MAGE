#include "pch.h"
#include "sprite.h"

namespace mage::game
{
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
}
