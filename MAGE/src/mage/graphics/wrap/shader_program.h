#pragma once
#include "pch.h"

namespace mage
{
	class shader_program : public COGA_RAN::shader_program
	{
	public:
		shader_program(const std::string& vertex, const std::string& fragment, bool textures, const coga::gfx::shader_preprocessor& p = coga::gfx::shader_preprocessor()) :
			COGA_RAN::shader_program({ coga::gfx::vertex_shader::create(vertex, p), coga::gfx::fragment_shader::create(fragment, p) })
		{
			if (textures)
			{
				const size_t count = coga::gfx::context::get_max_texture_units();
				int* samplers = new int[count];
				for (size_t i = 0; i < count; i++)
					samplers[i] = COGA_CAST(int, i);
				set_uniform_int_array(c::shader_textures, samplers, count);
				delete[] samplers;
			}
		}
		COGA_DCM(shader_program);
	};
}
