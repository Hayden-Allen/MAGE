#pragma once

#ifdef MAGE_PLATFORM_WINDOWS
	#ifdef MAGE_BUILD_DLL
		#define MAGE_API __declspec(dllexport)
	#else
		#define MAGE_API __declspec(dllimport)
	#endif
#else
	#error MAGE only supports Windows.
#endif

// for convenience to delete copy/move constructors
#define MAGE_DCM(name) \
	name(const name& other) = delete; \
	name(name&& other) = delete;
#define MAGE_DC(name) \
	name(const name& other) = delete;
// additional utils
#define MAGE_BIT(x) (1 << x)
#define MAGE_CAST(T, x) static_cast<T>(x)
#define MAGE_PUN(T, x) *(T*)&x
