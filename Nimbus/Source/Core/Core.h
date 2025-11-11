#pragma once

#ifdef NB_PLATFORM_WINDOWS
	#ifndef NB_BUILD_DLL
		#define NIMBUS_API __declspec(dllexport)
	#else
		#define NIMBUS_API __declspec(dllimport)
	#endif
#else
	#error Nimbus only supports Windows!
#endif

#ifdef NB_ENABLE_ASSERTS
	#define NB_ASSERT(x, ...) { if(!(x)) { NB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define NB_CORE_ASSERT(x, ...) { if(!(x)) { NB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define NB_ASSERT(x, ...)
	#define NB_CORE_ASSERT(x, ...)
#endif

#define BIT(n) (1 << n)

#define NB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)