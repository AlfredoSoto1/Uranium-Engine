#pragma once

#define	UR_MSVC_COMPILER
#define	UR_PLATFORM_WINDOWS

/*
* Check if platform is available before compiling
*/
#if !defined(UR_PLATFORM_WINDOWS) && !defined(UR_PLATFORM_LINUX)
	#error Urainum Engine only supports Windows and Linux platforms
#endif

/*
* Choose compiler for dll import/export
*/
#if defined(UR_MSVC_COMPILER)
	#define UR_EXPORT_DLL __declspec(dllexport)
	#define UR_IMPORT_DLL __declspec(dllimport)
#elif defined(UR_GCC_COMPILER)
	#define UR_EXPORT_DLL __attribute__((visibility("default")))
	#define UR_IMPORT_DLL __attribute__((visibility("hidden")))
#else
	#error Uranium-Engine only supports MSVC and GCC compilers
#endif

/*
* Check if the API wants to be exported or imported,
* as a third option is that does nothing since it would
* be linking as a static library
*/
#if defined(UR_BUILD_DLL)
	#define URANIUM_API UR_EXPORT_DLL
#elif defined(UR_USE_DLL)
	#define URANIUM_API UR_IMPORT_DLL
#else
	#define URANIUM_API
#endif

/*
* Check for platform to define the engine's debug breakpoint
*/
#if defined(UR_PLATFORM_WINDOWS) && defined(UR_DEBUG)
	#define UR_DEBUG_BREAK() __debugbreak()
#elif defined(UR_PLATFORM_LINUX) && defined(UR_DEBUG)
	#define UR_DEBUG_BREAK() __builtin_debugtrap()
#else
	#define UR_DEBUG_BREAK()
#endif

/*
* If debug enabled, define debug if statements
*/
#if defined(UR_DEBUG)
	#define UR_IF(condition, statement) if (condition) statement
#else 
	#define UR_IF(condition, statement)
#endif

/*
* This defines a scope to be executed only on
* UR_DEBUG configuration
*/
#if defined(UR_DEBUG)
	#define UR_ON_DEBUG(statement) statement
#else 
	#define UR_ON_DEBUG(statement)
#endif

/*
* This defines a scope that will only be executed only on
* UR_DEBUG configuration and it will swap to the second statement
* if the configuration is set to something different to UR_DEBUG.
*/
#if defined(UR_DEBUG)
	#define UR_ON_DEBUG_SWAP(debug_statement, release_statement) debug_statement
#else
	#define UR_ON_DEBUG_SWAP(debug_statement, release_statement) release_statement
#endif


#define UR_DECLARE class

#define UR_GENERIC(type, ...) template <class type, __VA_ARGS__>

#define UR_INTERFACE       class
#define UR_ABSTRACT_CLASS  class
#define UR_EXTENDS         public
#define UR_IMPLEMENTS      public

/*
* @brief
* Binds a class member function-method to an std::function<?>(...)
* You can pass as arguments the required paramenters for such
* member function to work.
*/
#define UR_BIND_FUNC(class_function, ...) std::bind(&class_function, this, __VA_ARGS__)