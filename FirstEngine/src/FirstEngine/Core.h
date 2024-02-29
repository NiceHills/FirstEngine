#pragma once

#ifdef FE_PLATFORM_WINDOWS
	#ifdef FE_BUILD_DLL
		#define FE_API _declspec(dllexport)
	#else
		#define FE_API _declspec(dllimport)
	#endif
#else
	#error FirstEngine only support Windows!
#endif
