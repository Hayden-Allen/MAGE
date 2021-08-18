#pragma once
#include "pch.h"

namespace n
{
	class static_vertex_array final : public MAGE_RAN::static_vertex_array {
	public:
		static_vertex_array(MAGE_RAN::static_vertex_buffer* const buffer, const s_desc& desc) :
			MAGE_RAN::static_vertex_array(buffer, desc)
		{}
		static_vertex_array(MAGE_RAN::retained_static_vertex_buffer* const buffer, const s_desc & desc) :
			MAGE_RAN::static_vertex_array(buffer, desc)
		{}
		N_DCM(static_vertex_array);
	};



	class dynamic_vertex_array final : public MAGE_RAN::dynamic_vertex_array {
	public:
		dynamic_vertex_array(MAGE_RAN::dynamic_vertex_buffer* const buffer, const s_desc& desc) :
			MAGE_RAN::dynamic_vertex_array(buffer, desc)
		{}
		dynamic_vertex_array(MAGE_RAN::retained_dynamic_vertex_buffer* const buffer, const s_desc & desc) :
			MAGE_RAN::dynamic_vertex_array(buffer, desc)
		{}
		N_DCM(dynamic_vertex_array);
	};
}
