#pragma once
#include "pch.h"

namespace mage::gl
{
	template<typename T>
	static GLenum get_type_enum()
	{
		MAGE_CORE_ASSERT(false, "Invalid GL enum type");
		return GL_NONE;
	}
	template<>
	static GLenum get_type_enum<float>()
	{
		return GL_FLOAT;
	}
	template<>
	static GLenum get_type_enum<uint32_t>()
	{
		return GL_UNSIGNED_INT;
	}
}
