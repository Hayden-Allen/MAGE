#include "pch.h"
#include "sprite_bank.h"
#include "sprite.h"

namespace n
{
	void sprite_bank::save(mage::output_file& out) const
	{
		const size_t count = get_size();
		out.ulong(count);
		for (size_t i = 0; i < count; i++)
			m_bank[i]->save(out);
	}
	void sprite_bank::load(mage::input_file& in)
	{
		m_next = in.ulong();
		for (size_t i = 0; i < m_next; i++)
		{
			m_bank[i] = new sprite(in);
			m_bank[i]->load(in);
		}
	}
}
