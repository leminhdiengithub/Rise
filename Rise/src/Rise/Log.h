#pragma once

#include<memory>
#include"Core.h"
#include"spdlog/spdlog.h"

namespace Rise {

	class RISE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetCilentLogger() { return s_CilentLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_CilentLogger;
	};
}

// Core log macros
#define RS_CORE_WARN(...)    ::Rise::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RS_CORE_INFO(...)    ::Rise::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RS_CORE_ERROR(...)   ::Rise::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RS_CORE_TRACE(...)   ::Rise::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RS_CORE_FATAL(...)   ::Rise::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Cilent log macros
#define RS_WARN(...)         ::Rise::Log::GetCilentLogger()->warn(__VA_ARGS__)
#define RS_INFO(...)         ::Rise::Log::GetCilentLogger()->info(__VA_ARGS__)
#define RS_ERROR(...)        ::Rise::Log::GetCilentLogger()->error(__VA_ARGS__)
#define RS_TRACE(...)        ::Rise::Log::GetCilentLogger()->trace(__VA_ARGS__)
#define RS_FATAL(...)        ::Rise::Log::GetCilentLogger()->fatal(__VA_ARGS__)

// if dist build
#define RS_CORE_INFO