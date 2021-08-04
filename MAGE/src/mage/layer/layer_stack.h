#pragma once
#include "pch.h"
#include "layer.h"

namespace mage
{
	/**
	 * Data structure to manage application layers. Supports attaching to/detaching from the middle and top of the stack.
	 */
	class MAGE_API layer_stack
	{
		typedef std::vector<layer*> list;
	public:
		layer_stack() {}
		MAGE_DCM(layer_stack);
		~layer_stack();


		void attach(layer* const layer);
		void detach(layer* const layer);
		void attach_top(layer* const layer);
		void detach_top(layer* const layer);
		list::iterator begin()
		{
			return m_layers.begin();
		}
		list::iterator end()
		{
			return m_layers.end();
		}
		list::const_iterator begin() const
		{
			return m_layers.cbegin();
		}
		list::const_iterator end() const
		{
			return m_layers.cend();
		}
	private:
		list m_layers;
		list::iterator m_insert;


		void detach_base(layer* const layer);
	};
}
