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

#define BIT(n) (1 << n)