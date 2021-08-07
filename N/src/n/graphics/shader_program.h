#pragma once
#include "pch.h"

namespace n
{
	N_WRAP
	(
		shader_program,
		shader_program,
		(const std::string& vertex, const std::string& fragment, const mage::gfx::shader_preprocessor& p = mage::gfx::shader_preprocessor()),
		(
			{
				mage::gfx::vertex_shader::create(vertex, p),
				mage::gfx::fragment_shader::create(fragment, p)
			}
		)
	);
}
