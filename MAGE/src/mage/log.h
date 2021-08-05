#pragma once
#include "pch.h"

namespace mage
{
	class log
	{
	public:
		static void init();
		static spdlog::logger* const get_core();
		static spdlog::logger* const get_client();
	private:
		static spdlog::logger* s_core;
		static spdlog::logger* s_client;
	};
}



#ifndef MAGE_DIST
	#define MAGE_CORE_TRACE(...) ::mage::log::get_core()->trace(__VA_ARGS__)
	#define MAGE_CORE_INFO(...)  ::mage::log::get_core()->info(__VA_ARGS__)
	#define MAGE_CORE_WARN(...)  ::mage::log::get_core()->warn(__VA_ARGS__)
	#define MAGE_CORE_ERROR(...) ::mage::log::get_core()->error(__VA_ARGS__)
	#define MAGE_TRACE(...)		 ::mage::log::get_client()->trace(__VA_ARGS__)
	#define MAGE_INFO(...)		 ::mage::log::get_client()->info(__VA_ARGS__)
	#define MAGE_WARN(...)		 ::mage::log::get_client()->warn(__VA_ARGS__)
	#define MAGE_ERROR(...)		 ::mage::log::get_client()->error(__VA_ARGS__)
#else
	#define MAGE_CORE_TRACE(...)
	#define MAGE_CORE_INFO(...) 
	#define MAGE_CORE_WARN(...) 
	#define MAGE_CORE_ERROR(...)
	#define MAGE_TRACE(...)
	#define MAGE_INFO(...) 
	#define MAGE_WARN(...) 
	#define MAGE_ERROR(...)
#endif



#ifdef MAGE_DEBUG
	#define MAGE_CORE_ASSERT(x, ...) if(!(x)) { MAGE_CORE_FATAL("Assertion failed {}", __VA_ARGS__); __debug_break(); }
	#define MAGE_ASSERT(x, ...) if(!(x)) { MAGE_FATAL("Assertion failed {}", __VA_ARGS__); __debug_break(); }
#else
	#define MAGE_CORE_ASSERT(x, ...)
	#define MAGE_ASSERT(x, ...)
#endif
