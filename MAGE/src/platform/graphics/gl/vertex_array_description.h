#pragma once
#include "pch.h"
#include "mage/graphics/vertex_array_description.h"

namespace mage::gl
{
	class vertex_array_description final : public mage::gfx::vertex_array_description
	{
	public:
		typedef std::initializer_list<uint32_t> s_type;


		vertex_array_description(const std::initializer_list<uint32_t>& desc) :
			m_desc(desc)
		{}
		MAGE_DCM(vertex_array_description);


		const s_type& get_desc() const
		{
			return m_desc;
		}
	protected:
		 s_type m_desc;
	};
}
