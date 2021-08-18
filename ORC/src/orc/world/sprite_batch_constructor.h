#pragma once
#include "pch.h"
#include "orc/graphics/sprite_bank.h"

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
	public:
		bool can_contain(const sprite_bank& sb, const n::tile& t) const;
		void add(const sprite_bank& sb, const n::tile& t);
	private:
		std::unordered_set<n::sprite_atlas_bank::handle> m_atlases;
		std::unordered_map<const sprite*, std::vector<n::tile>> m_tiles;
	private:
		static size_t get_max_atlas_count()
		{
			return mage::gfx::context::get_max_texture_units();
		}
	};
}
