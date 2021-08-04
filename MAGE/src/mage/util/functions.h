#pragma once
#include "pch.h"

namespace mage
{
	template<typename T, size_t N>
	size_t arrlen(const T(&arr)[N])
	{
		return N;
	}
	template<typename T, size_t N>
	size_t arrsize(const T(&arr)[N])
	{
		return N * sizeof(T);
	}
}
