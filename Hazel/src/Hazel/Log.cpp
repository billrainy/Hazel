#include "Log.h"

namespace Hazel{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;  //类的静态成员变量的类外初始化：分配空间，否则会引发链接错误
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}