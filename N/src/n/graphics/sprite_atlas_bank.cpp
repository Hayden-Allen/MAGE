#include "pch.h"
#include "sprite_atlas_bank.h"
#include "sprite_atlas.h"

namespace n
{
	void sprite_atlas_bank::save(mage::output_file& out) const
	{
		const size_t count = get_size();
		out.ulong(count);
		for (size_t i = 0; i < count; i++)
			m_bank[i]->save(out);
	}
	void sprite_atlas_bank::load(mage::input_file& in)
	{
		m_next = in.ulong();
		for (size_t i = 0; i < m_next; i++)
		{
			m_bank[i] = new sprite_atlas(this);
			m_bank[i]->load(in);
		}
	}
}
