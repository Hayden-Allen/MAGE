#pragma once
#include "pch.h"
#include "chunk.h"
#include "mage/graphics/sprite.h"
#include "sprite_batch_bank.h"

namespace mage
{
	template<typename SAB, typename SB, typename SBB, typename C>
	class map_base : public coga::serializable
	{
	protected:
		typedef std::unordered_map<size_t, std::unordered_map<size_t, C*>> grid;
	public:
		COGA_DCM(map_base);
		~map_base()
		{
			delete m_atlases;
			delete m_sprites;
			for (auto& row : m_chunks)
				for (auto& pair : row.second)
					delete pair.second;
		}
	public:
		void load(coga::input_file& in) override
		{
			m_sprites = new SB(in);
			m_atlases = new SAB(in);

			m_chunk_count = in.ulong();
		}
		void draw(const coga::timestep& t, const mage::shader_program& shader)
		{
			/**
			 * TODO bad
			 */
			for (auto& row : m_chunks)
				for (auto& pair : row.second)
					pair.second->draw(t, m_sprites, m_atlases, shader);
		}
	protected:
		SAB* m_atlases;
		SB* m_sprites;
		grid m_chunks;
		size_t m_chunk_count;
	protected:
		map_base() :
			m_atlases(nullptr),
			m_sprites(nullptr),
			m_chunk_count(0)
		{}
		map_base(SAB* const atlases, SB* const sprites) :
			m_atlases(atlases),
			m_sprites(sprites),
			m_chunk_count(0)
		{}
	protected:
		void add_chunk(C* const c)
		{
			const auto& pos = c->get_pos();
			if (!m_chunks.contains(pos.y))
				m_chunks.insert({ pos.y, {} });
			if (m_chunks[pos.y].contains(pos.x))
				COGA_ASSERT(false, "Overlapping chunks at <{}, {}>", pos.x, pos.y);

			m_chunks[pos.y][pos.x] = c;
		}
	};



	class map final : public map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>
	{
	public:
		map(coga::input_file& in)
		{
			load(in);
		}
	public:
		void save(coga::output_file& out) const override
		{
			COGA_ASSERT(false, "Cannot save a mage::map");
		}
		void load(coga::input_file& in)
		{
			map_base<sprite_atlas_bank, sprite_bank, sprite_batch_bank, chunk>::load(in);

			for (size_t i = 0; i < m_chunk_count; i++)
				add_chunk(new chunk(in));
		}
	};
}
