#include "pch.h"
#include "sprite_batch_constructor.h"
#include "orc/graphics/sprite.h"

namespace orc
{
	bool sprite_batch_constructor::can_contain(const orc::tile& t) const
	{
		// compute the number of atlases that the given tile's sprite uses that are not already part of this batch
		size_t additional = 0;
		for (const auto& a : t.sprite->get_atlases())
			additional += !m_atlases.contains(a);
		// if adding the required atlases for the given tile would result in this batch having more atlases than can bound at a time, reject the tile
		return (m_atlases.size() + additional) <= get_max_atlas_count();
	}
	void sprite_batch_constructor::add(const orc::tile& t)
	{
		// add any new atlases (m_atlases is a set)
		const auto& atlases = t.sprite->get_atlases();
		m_atlases.insert(atlases.begin(), atlases.end());

		// add given tile to its sprite's list of tiles, or create a list if it doesn't exist
		const auto& it = m_tiles.find(t.sprite);
		if (it != m_tiles.end())
			it->second.push_back(t);
		else
			m_tiles.insert({ t.sprite, { t } });
	}
}
