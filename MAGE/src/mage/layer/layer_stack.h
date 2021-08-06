#pragma once
#include "pch.h"
#include "layer.h"
#include "mage/util/iterable.h"

namespace mage
{
	/**
	 * Data structure to manage application layers. Supports attaching to/detaching from the middle and top of the stack.
	 */
	class layer_stack final : public iterable<std::vector<layer*>>
	{
	public:
		layer_stack() :
			m_insert(0)
		{}
		MAGE_DCM(layer_stack);
		~layer_stack();


		void attach(s_type const layer);
		void detach(s_type const layer);
		void attach_top(s_type const layer);
		void detach_top(s_type const layer);
	private:
		size_t m_insert;


		void detach_base(s_type const layer);
	};
}
