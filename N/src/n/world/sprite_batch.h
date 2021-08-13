#pragma once
#include "pch.h"
#include "tile.h"
#include "n/timestep.h"
#include "n/graphics/sprite_atlas_bank.h"
#include "n/graphics/sprite_bank.h"
#include "n/graphics/wrap/buffer.h"
#include "n/graphics/wrap/shader_program.h"
#include "n/graphics/wrap/vertex_array.h"

namespace n
{
	class sprite_batch_constructor final
	{
		friend class sprite_batch;
	public:
		sprite_batch_constructor() {}
		sprite_batch_constructor(const sprite_batch_constructor& other) :
			m_atlases(other.m_atlases),
			m_tiles(other.m_tiles)
		{}
		sprite_batch_constructor(sprite_batch_constructor&& other) :
			m_atlases(other.m_atlases),
			m_tiles(other.m_tiles)
		{}


		bool can_contain(const tile& t) const;
		void add(const tile& t);
	private:
		std::unordered_set<sprite_atlas_bank::handle> m_atlases;
		std::unordered_map<sprite*, std::vector<tile>> m_tiles;


		static size_t get_max_atlas_count()
		{
			return mage::gfx::context::get_max_texture_units();
		}
	};



	class sprite_batch final
	{
	public:
		sprite_batch(const sprite_batch_constructor& constructor);
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) :
			m_indices(other.m_indices),
			m_vertices(other.m_vertices),
			m_vertex_array(other.m_vertex_array),
			m_atlases(other.m_atlases),
			m_sprites(other.m_sprites),
			m_sprite_atlases(other.m_sprite_atlases),
			m_offsets(other.m_offsets)
		{
			other.m_indices = nullptr;
			other.m_vertices = nullptr;
			other.m_vertex_array = nullptr;
			other.m_sprite_atlases = nullptr;
			other.m_offsets = nullptr;
		}
		~sprite_batch();


		void draw(const timestep& t, sprite_bank* const sb, const sprite_atlas_bank* const ab, const shader_program& shader);
	private:
		static_index_buffer* m_indices;
		static_vertex_buffer* m_vertices;
		static_vertex_array* m_vertex_array;
		std::vector<sprite_atlas_bank::handle> m_atlases;
		std::vector<sprite_bank::handle> m_sprites;
		sprite_atlas_bank::handle* m_sprite_atlases;
		glm::vec2* m_offsets;

	};
}
