#include "pch.h"
#include "log.h"

namespace mage
{
	std::shared_ptr<spdlog::logger> log::s_core;
	std::shared_ptr<spdlog::logger> log::s_client;



	void log::init()
	{
		spdlog::set_pattern("%^[%T | %n]: %v%$");
		s_core = spdlog::stdout_color_mt("MAGE");
		s_core->set_level(spdlog::level::trace);
		s_client = spdlog::stdout_color_mt("APP ");
		s_client->set_level(spdlog::level::trace);
	}
	const std::shared_ptr<spdlog::logger>& log::get_core()
	{
		return s_core;
	}
	const std::shared_ptr<spdlog::logger>& log::get_client()
	{
		return s_client;
	}
}
