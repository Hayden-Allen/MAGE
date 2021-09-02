#include "pch.h"
#include "dynamic.h"
#include "mage/graphics/sprite.h"

namespace mage
{
	dynamic::dynamic(dynamic_list& dl, const glm::vec2& pos, const glm::vec2& vel, float speed, const std::unordered_map<std::string, sprite*>& states, const std::string& state) :
		coga::vector_positional(pos),
		coga::bounded_movable(vel, speed),
		coga::stateful<std::string, sprite*>(states, state),
		m_vertices{ 0.f },
		m_handle(dl.add(this))
	{}



	void dynamic::update_vertices()
	{
		const sprite* const sprite = get_state();

		const float sw = .5f * sprite->get_w(), sh = .5f * sprite->get_h();
		const float dims[] = { -sw, -sh, sw, -sh, sw, sh, -sw, sh };

		const sprite_atlas_coords& base_coords = sprite->get_base_coords();
		const glm::vec2& frame_offset = sprite->get_current_frame().offset;
		const glm::vec2& min = frame_offset + glm::vec2(base_coords.x.get_min(), base_coords.y.get_min());
		const glm::vec2& max = frame_offset + glm::vec2(base_coords.x.get_max(), base_coords.y.get_max());
		const float tex[] = { min.x, min.y, max.x, min.y, max.x, max.y, min.x, max.y };

		for (size_t i = 0; i < c::vertices_per_tile; i++)
		{
			const size_t off = i * c::floats_per_dynamic_vertex;
			// x, y
			m_vertices[off + 0] = m_pos.x + dims[i * 2 + 0];
			m_vertices[off + 1] = m_pos.y + dims[i * 2 + 1];
			// s, t
			m_vertices[off + 2] = tex[i * 2 + 0];
			m_vertices[off + 3] = tex[i * 2 + 1];
			// i
			m_vertices[off + 4] = 1.f * m_handle.texture;
			// cy
			m_vertices[off + 5] = m_pos.y;
		}
	}
}
