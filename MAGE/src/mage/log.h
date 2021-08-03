#pragma once
#include "pch.h"

namespace mage
{
	class log
	{
	public:
		static MAGE_API void init();
		static MAGE_API const std::shared_ptr<spdlog::logger>& get_core();
		static MAGE_API const std::shared_ptr<spdlog::logger>& get_client();
	private:
		static MAGE_API std::shared_ptr<spdlog::logger> s_core;
		static MAGE_API std::shared_ptr<spdlog::logger> s_client;
	};
}


#ifndef MAGE_BUILD_PRODUCTION
	#define MAGE_CORE_TRACE(...) ::mage::log::get_core()->trace(__VA_ARGS__)
	#define MAGE_CORE_INFO(...)  ::mage::log::get_core()->info(__VA_ARGS__)
	#define MAGE_CORE_WARN(...)  ::mage::log::get_core()->warn(__VA_ARGS__)
	#define MAGE_CORE_ERROR(...) ::mage::log::get_core()->error(__VA_ARGS__)
	#define MAGE_CORE_FATAL(...) ::mage::log::get_core()->fatal(__VA_ARGS__)
	#define MAGE_TRACE(...)		 ::mage::log::get_client()->trace(__VA_ARGS__)
	#define MAGE_INFO(...)		 ::mage::log::get_client()->info(__VA_ARGS__)
	#define MAGE_WARN(...)		 ::mage::log::get_client()->warn(__VA_ARGS__)
	#define MAGE_ERROR(...)		 ::mage::log::get_client()->error(__VA_ARGS__)
	#define MAGE_FATAL(...)		 ::mage::log::get_client()->fatal(__VA_ARGS__)
#else
	#define MAGE_CORE_TRACE(...)
	#define MAGE_CORE_INFO(...) 
	#define MAGE_CORE_WARN(...) 
	#define MAGE_CORE_ERROR(...)
	#define MAGE_CORE_FATAL(...)
	#define MAGE_TRACE(...)
	#define MAGE_INFO(...) 
	#define MAGE_WARN(...) 
	#define MAGE_ERROR(...)
	#define MAGE_FATAL(...)
#endif