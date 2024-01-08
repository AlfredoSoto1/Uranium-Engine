#pragma once

#define	UR_PLATFORM_WINDOWS

#if defined(UR_PLATFORM_WINDOWS)

#define UR_DEBUG_BREAK() __debugbreak()

#if defined(UR_BUILD_DLL)
// Build Engine to export to dll
#define URANIUM_API __declspec(dllexport)
#elif defined(UR_USE_DLL)
// Build Engine to load dll
#define URANIUM_API __declspec(dllimport)
#else
// Build Engine as static lib
#define URANIUM_API
#endif

#elif defined(UR_PLATFORM_LINUX)

#error Urainum Engine does not support Linux at the moment
#define UR_DEBUG_BREAK() __builtin_debugtrap()

#if defined(UR_BUILD_DLL)
#define URANIUM_API 
#elif defined(UR_USE_DLL)
#define URANIUM_API 
#else
// Build Engine as static lib
#define URANIUM_API
#endif

#else
#error Urainum Engine only supports Windows and Linux platforms
#endif
