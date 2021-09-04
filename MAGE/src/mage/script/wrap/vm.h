#pragma once
#include "pch.h"
#include "script.h"

namespace mage::sasm
{
	class vm final : public hasl::sasm::vm<c::script_stack_size, c::script_ram_size>
	{
	public:
		vm() :
			hasl::sasm::vm<c::script_stack_size, c::script_ram_size>()
		{}
		COGA_DCM(vm);
	public:
		hasl::sasm::i_t run(script& s, hasl::sasm::script_runtime& rt, const hasl::sasm::v_t& scroll)
		{
			m_scroll = scroll;
			return hasl::sasm::vm<c::script_stack_size, c::script_ram_size>::run(s, rt);
		}
	protected:
		hasl::sasm::v_t m_scroll;
	protected:
		hasl::sasm::scriptable* spawn(const char* s)
		{
			printf("SPAWN '%s'\n", s);
			return nullptr;
		}
		void process_spawn_queue(hasl::sasm::script_runtime& rt)
		{
			for (const auto& s : m_spawn_queue)
				printf("PROCESS '%p'\n", s);
		}
		bool is_key_pressed(hasl::sasm::i_t key) const
		{
			return COGA_IN.is_key_pressed(COGA_CAST(int, key));
		}
		bool is_mouse_pressed(hasl::sasm::i_t button) const
		{
			return COGA_IN.is_mouse_pressed(COGA_CAST(int, button));
		}
		hasl::sasm::v_t get_mouse_pos() const
		{
			const glm::vec2& p = COGA_IN.get_mouse_pos();
			return { p.x, p.y };
		}
		hasl::sasm::v_t get_mouse_scroll() const
		{
			return m_scroll;
		}
	};
}
