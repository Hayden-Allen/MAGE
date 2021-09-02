#pragma once
#include "pch.h"

namespace mage
{
	class static_vertex_array final : public COGA_RAN::static_vertex_array {
	public:
		static_vertex_array(COGA_RAN::static_vertex_buffer* const buffer, const s_desc& desc) :
			COGA_RAN::static_vertex_array(buffer, desc)
		{}
		static_vertex_array(COGA_RAN::retained_static_vertex_buffer* const buffer, const s_desc & desc) :
			COGA_RAN::static_vertex_array(buffer, desc)
		{}
		COGA_DCM(static_vertex_array);
	};



	class dynamic_vertex_array final : public COGA_RAN::dynamic_vertex_array {
	public:
		dynamic_vertex_array(COGA_RAN::dynamic_vertex_buffer* const buffer, const s_desc& desc) :
			COGA_RAN::dynamic_vertex_array(buffer, desc)
		{}
		dynamic_vertex_array(COGA_RAN::retained_dynamic_vertex_buffer* const buffer, const s_desc & desc) :
			COGA_RAN::dynamic_vertex_array(buffer, desc)
		{}
		COGA_DCM(dynamic_vertex_array);
	};
}
