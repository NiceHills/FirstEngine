#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace FirstEngine {

	class FE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return s_Corelogger;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_Clientlogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Corelogger;
		static std::shared_ptr<spdlog::logger> s_Clientlogger;
	};
}
// Core log macros
#define FE_CORE_TRACE(...)	::FirstEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FE_CORE_INFO(...)	::FirstEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FE_CORE_WARN(...)	::FirstEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FE_CORE_ERROR(...)	::FirstEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FE_CORE_FATAL(...)	::FirstEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Core log macros
#define FE_TRACE(...)		::FirstEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FE_INFO(...)		::FirstEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define FE_WARN(...)		::FirstEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FE_ERROR(...)		::FirstEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define FE_FATAL(...)		::FirstEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

