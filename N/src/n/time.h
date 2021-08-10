#pragma once
#include "pch.h"

namespace n
{
	typedef std::chrono::time_point<std::chrono::steady_clock> time;



	static time get_time()
	{
		return std::chrono::steady_clock::now();
	}
}
