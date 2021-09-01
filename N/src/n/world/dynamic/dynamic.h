#pragma once
#include "pch.h"
#include "dynamic_list.h"

namespace n
{
	class sprite;

	class dynamic :
		public mage::vector_positional,
		public mage::bounded_movable,
		public mage::stateful<std::string, sprite*>
	{
		friend class dynamic_list;
	public:
		dynamic(dynamic_list& dl, const glm::vec2& pos, const glm::vec2& vel, float speed, const std::unordered_map<std::string, sprite*>& states, const std::string& state);
		N_DCM(dynamic);
	public:
		void update(float dt)
		{
			m_pos += m_vel * dt;
		}
		const float* const get_vertices() const
		{
			return m_vertices;
		}
	private:
		// hitbox* m_hitbox;
		// bool m_added;
		float m_vertices[c::floats_per_dynamic];
		dynamic_list::handle m_handle;
	private:
		void update_vertices();
		// void init(qtnode* const root);
	};
}
