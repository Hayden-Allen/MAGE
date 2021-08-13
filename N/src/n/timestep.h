#pragma once
#include "pch.h"

namespace n
{
	class timestep final
	{
	public:
		timestep() :
			m_time(std::chrono::steady_clock::now())
		{}


		float operator-(const timestep& other) const
		{
			return std::chrono::duration<float, std::milli>(m_time - other.m_time).count();
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_time;
	};
}