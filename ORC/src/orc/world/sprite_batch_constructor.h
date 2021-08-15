#pragma once
#include "pch.h"
#include "tile.h"

namespace orc
{
	class sprite;

	class sprite_batch_constructor final
	{
		friend class sprite_batch;
	public:
		sprite_batch_constructor() {}
		sprite_batch_constructor(const sprite_batch_constructor& other) :
			m_atlases(other.m_atlases),
			m_tiles(other.m_tiles)
		{}
		sprite_batch_constructor(sprite_batch_constructor&& other) noexcept :
			m_atlases(other.m_atlases),
			m_tiles(other.m_tiles)
		{}


		bool can_contain(const orc::tile& t) const;
		void add(const orc::tile& t);
	private:
		std::unordered_set<n::sprite_atlas_bank::handle> m_atlases;
		std::unordered_map<sprite*, std::vector<orc::tile>> m_tiles;


		static size_t get_max_atlas_count()
		{
			return mage::gfx::context::get_max_texture_units();
		}
	};
}
