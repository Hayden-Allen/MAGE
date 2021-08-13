#pragma once
#include "pch.h"

namespace n
{
	N_WRAP
	(
		static_index_buffer,
		static_index_buffer,
		(s_type* indices, size_t count),
		(indices, count)
	);



	N_WRAP
	(
		dynamic_index_buffer,
		dynamic_index_buffer,
		(s_type* indices, size_t count),
		(indices, count)
	);



	N_WRAP
	(
		static_vertex_buffer,
		static_vertex_buffer,
		(s_type* vertices, size_t count),
		(vertices, count)
	);



	N_WRAP
	(
		dynamic_vertex_buffer,
		dynamic_vertex_buffer,
		(s_type* vertices, size_t count),
		(vertices, count)
	);
}
