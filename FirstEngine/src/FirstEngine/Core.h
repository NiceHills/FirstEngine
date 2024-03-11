#pragma once

#ifdef FE_PLATFORM_WINDOWS
	#if FE_DYNAMIC_LINK
		#ifdef FE_BUILD_DLL
			#define FE_API _declspec(dllexport)
		#else
			#define FE_API _declspec(dllimport)
		#endif
	#else 
		#define FE_API
	#endif
#else
	#error FirstEngine only support Windows!
#endif

#ifdef FE_DEBUG
	#define FE_ENABLE_ASSERTS
#endif


#ifdef FE_ENABLE_ASSERTS
	#define FE_ASSERT(x, ...) {if(!(x)){ FE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define FE_CORE_ASSERT(x, ...) {if(!(x)) {FE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define FE_ASSERT(x, ...)
	#define FE_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
