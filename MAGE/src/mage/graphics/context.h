#pragma once
#include "pch.h"

namespace mage::gfx
{
	class context
	{
	public:
		MAGE_DCM(context);
		virtual ~context() {}


		static context* create(void* const host, uint32_t w, uint32_t h, const std::string& title);
		template<typename T = void*>
		T const get_window() const
		{
			return MAGE_CAST(T, m_window);
		}
	protected:
		void* m_window;


		context() :
			m_window(nullptr)
		{}
	};
}
