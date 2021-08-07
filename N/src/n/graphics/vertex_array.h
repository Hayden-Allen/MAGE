#pragma once
#include "pch.h"

namespace n
{
	N_WRAP
	(
		static_vertex_array,
		static_vertex_array,
		(MAGE_RAN::static_vertex_buffer* const buffer, const s_desc& desc),
		(buffer, desc)
	);



	N_WRAP
	(
		dynamic_vertex_array,
		dynamic_vertex_array,
		(MAGE_RAN::dynamic_vertex_buffer* const buffer, const s_desc& desc),
		(buffer, desc)
	);
}
