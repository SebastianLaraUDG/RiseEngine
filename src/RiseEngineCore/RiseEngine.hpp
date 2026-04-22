#pragma once

#ifdef _MSC_VER
	
	#ifdef RISE_ENGINE_BUILD_DLL
		#define RISE_API __declspec(dllexport)
	#else
	#define RISE_API __declspec(dllimport)

#endif // RISE_ENGINE_BUILD_DLL

#elif defined(__GNUC__) || __cpp_user_defined_literals(__clang__) // GCC/Clang
#ifdef RISE_ENGINE_BUILD_DLL
#define RISE_API __attribute__((visibility("default")))
#else
#define RISE_API
#endif // RISE_ENGINE_BUILD_DLL
#else
#define RISE_API
#endif // _MSC_VER