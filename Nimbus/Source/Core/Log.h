#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h"

namespace Nimbus
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define NB_CORE_TRACE(...)    ::Nimbus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NB_CORE_INFO(...)     ::Nimbus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NB_CORE_WARN(...)     ::Nimbus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NB_CORE_ERROR(...)    ::Nimbus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NB_CORE_CRITICAL(...) ::Nimbus::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Core Log Macros
#define NB_TRACE(...)         ::Nimbus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NB_INFO(...)          ::Nimbus::Log::GetClientLogger()->info(__VA_ARGS__)
#define NB_WARN(...)          ::Nimbus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NB_ERROR(...)         ::Nimbus::Log::GetClientLogger()->error(__VA_ARGS__)
#define NB_CRITICAL(...)      ::Nimbus::Log::GetClientLogger()->critical(__VA_ARGS__)