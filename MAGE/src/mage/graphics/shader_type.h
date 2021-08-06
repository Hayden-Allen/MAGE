#pragma once
#include "pch.h"

namespace mage::gfx
{
	enum class shader_type
	{
		none = 0,
		boolean,
		int1, int2, int3, int4,
		uint1, uint2, uint3, uint4,
		float1, float2, float3, float4,
		mat3, mat4
	};
	template<typename R, typename T>
	static R get_shader_type();



	static size_t shader_type_element_count[] =
	{
		0,
		1,
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4,
		3 * 3, 4 * 4
	};
	static size_t get_shader_type_element_count(shader_type t)
	{
		MAGE_CORE_ASSERT(t != shader_type::none, "Invalid shader type");
		return shader_type_element_count[MAGE_CAST(size_t, t)];
	}



	static size_t shader_type_base_size[] =
	{
		0,
		sizeof(bool),
		sizeof(int), sizeof(int), sizeof(int), sizeof(int),
		sizeof(unsigned int), sizeof(unsigned int), sizeof(unsigned int), sizeof(unsigned int),
		sizeof(float), sizeof(float), sizeof(float), sizeof(float),
		sizeof(float), sizeof(float)
	};
	static size_t get_shader_type_base_size(shader_type t)
	{
		MAGE_CORE_ASSERT(t != shader_type::none, "Invalid shader type");
		return shader_type_base_size[MAGE_CAST(size_t, t)];
	}



	template<typename T>
	static T get_shader_type_base(shader_type t);
}
