#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel{
	class HAZEL_API Log
	{
	public:
		static void Init();  //为logger变量赋值

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;  //静态成员变量类内声明时，并未为其分配内存
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//Core log macros
#define HZ_CORE_TRACE(...)   ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)  //static member functions can only be invoked by class
#define HZ_CORE_INFO(...)    ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)    ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)   ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define HZ_CORE_FATAL(...) ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define HZ_Client_TRACE(...)   ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_Client_INFO(...)    ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_Client_WARN(...)    ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_Client_ERROR(...)   ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
//#define HZ_Client_FATAL(...) ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)