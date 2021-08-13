#pragma once
#include "pch.h"

namespace n
{
	class shader_program : public MAGE_RAN::shader_program
	{
	public:
		shader_program(const std::string& vertex, const std::string& fragment, bool textures, const mage::gfx::shader_preprocessor& p = mage::gfx::shader_preprocessor()) :
			MAGE_RAN::shader_program({ mage::gfx::vertex_shader::create(vertex, p), mage::gfx::fragment_shader::create(fragment, p) })
		{
			if (textures)
			{
				const size_t count = mage::gfx::context::get_max_texture_units();
				int* samplers = new int[count];
				for (size_t i = 0; i < count; i++)
					samplers[i] = MAGE_CAST(int, i);
				set_uniform_int_array(c::shader_textures, samplers, count);
				delete[] samplers;
			}
		}
		N_DCM(shader_program);
	};
}
