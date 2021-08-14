#include "pch.h"
#include "sprite_batch.h"

namespace n
{
	sprite_batch::~sprite_batch()
	{
		delete m_indices;
		delete m_vertices;
		delete m_vertex_array;
		delete m_sprites;
		delete m_offsets;
		delete m_texture_indices;
	}



	void sprite_batch::draw(const mage::timestep& t, mage::game::sprite_bank* const sb, const mage::game::sprite_atlas_bank* const ab, const shader_program& shader)
	{
		// for each sprite in this batch
		for (size_t i = 0; i < m_sprite_count; i++)
		{
			// update the current sprite
			mage::game::sprite* const s = sb->get(m_sprites[i]);
			s->update(t);

			const auto& state = s->get_current_frame();
			// get texture coord offsets for current frame
			m_offsets[i] = state.offset;
			// get atlas index for current frame. This is used by the shader as an index into m_texture_indices, which in turn yields the actual texture slot that this bank is bound to
			m_texture_indices[i] = state.bank;
		}
		// bind all atlases to their pre-determined indices
		for (const auto& pair : m_atlases)
			ab->get(pair.first)->bind(MAGE_CAST(uint32_t, pair.second));

		// upload current arrays
		shader.set_uniform_int_array(mage::game::c::shader_sprite_to_texture_indices, m_texture_indices, m_sprite_count);
		shader.set_uniform_float2_array(mage::game::c::shader_sprite_offsets, m_offsets, m_sprite_count);
		
		// draw all tiles
		mage::gfx::renderer::draw(m_indices, m_vertex_array);
	}
}
