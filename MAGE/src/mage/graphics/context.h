#pragma once
#include "pch.h"

namespace mage::gfx
{
	class context
	{
	public:
		MAGE_DCM(context);
		virtual ~context() {}
	public:
		static context* create(void* const host, uint32_t w, uint32_t h, const std::string& title);
		static size_t get_max_texture_units();
		template<typename T = void*>
		T const get_window() const
		{
			return MAGE_CAST(T, m_window);
		}
	protected:
		void* m_window;
	protected:
		context() :
			m_window(nullptr)
		{}
	};
}
