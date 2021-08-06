#pragma once
#include "pch.h"

namespace mage::gfx
{
	typedef uint32_t renderer_id_t;



	class render_object
	{
	public:
		render_object() :
			m_id(0)
		{}
		MAGE_DCM(render_object);


		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		renderer_id_t get_id() const
		{
			return m_id;
		}
	protected:
		renderer_id_t m_id;
	};
}
