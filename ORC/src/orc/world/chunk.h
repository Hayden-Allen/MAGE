#pragma once
#include "pch.h"
#include "tile.h"

namespace orc
{
	class chunk final : public n::chunk
	{
	public:
		chunk(const std::vector<tile>& tiles);
		N_DCM(chunk);


		bool is_empty() const
		{
			return m_tile_count == 0;
		}
	private:
		mage::game::sprite_bank::handle m_grid[mage::game::c::tiles_per_chunk];
		size_t m_tile_count;
	};
}
