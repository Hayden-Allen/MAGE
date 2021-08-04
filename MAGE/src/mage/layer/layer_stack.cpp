#include "pch.h"
#include "layer_stack.h"
#include "log.h"

namespace mage
{
	layer_stack::~layer_stack()
	{
		for (layer* l : m_layers)
			delete l;
	}



	void layer_stack::attach(layer* const layer)
	{
		m_insert = m_layers.insert(m_insert, layer);
		layer->on_attach();
	}
	void layer_stack::detach(layer* const layer)
	{
		detach_base(layer);
		m_insert--;
	}
	void layer_stack::attach_top(layer* const layer)
	{
		m_layers.push_back(layer);
		layer->on_attach();
	}
	void layer_stack::detach_top(layer* const layer)
	{
		detach_base(layer);
	}



	void layer_stack::detach_base(layer* const layer)
	{
		const auto& it = std::find(m_layers.begin(), m_layers.end(), layer);
		MAGE_CORE_ASSERT(it != m_layers.end(), "Attempted to detach a layer that is not part of the layer_stack");
		m_layers.erase(it);
		layer->on_detach();
	}
}
