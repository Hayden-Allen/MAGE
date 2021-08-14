#pragma once
#include "pch.h"
#include "tile.h"
#include "n/graphics/wrap/buffer.h"
#include "n/graphics/wrap/shader_program.h"
#include "n/graphics/wrap/vertex_array.h"

namespace n
{
	class sprite_batch
	{
	public:
		N_DC(sprite_batch);
		sprite_batch(sprite_batch&& other) noexcept :
			m_indices(other.m_indices),
			m_vertices(other.m_vertices),
			m_vertex_array(other.m_vertex_array),
			m_sprite_count(other.m_sprite_count),
			m_atlases(other.m_atlases),
			m_sprites(other.m_sprites),
			m_offsets(other.m_offsets),
			m_texture_indices(other.m_texture_indices)
		{
			other.m_indices = nullptr;
			other.m_vertices = nullptr;
			other.m_vertex_array = nullptr;
			other.m_sprites = nullptr;
			other.m_offsets = nullptr;
			other.m_texture_indices = nullptr;
		}
		virtual ~sprite_batch();


		void draw(const mage::timestep& t, mage::game::sprite_bank* const sb, const mage::game::sprite_atlas_bank* const ab, const shader_program& shader);
	protected:
		static_index_buffer* m_indices;
		static_vertex_buffer* m_vertices;
		static_vertex_array* m_vertex_array;
		size_t m_sprite_count;
		std::unordered_map<mage::game::sprite_atlas_bank::handle, size_t> m_atlases;
		mage::game::sprite_bank::handle* m_sprites;
		glm::vec2* m_offsets;
		int* m_texture_indices;


		sprite_batch() :
			m_indices(nullptr),
			m_vertices(nullptr),
			m_vertex_array(nullptr),
			m_sprite_count(0),
			m_sprites(nullptr),
			m_offsets(nullptr),
			m_texture_indices(nullptr)
		{}
	};
}
