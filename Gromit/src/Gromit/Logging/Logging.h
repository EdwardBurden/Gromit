#pragma once
#include "../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Gromit {

	class GROMIT_API Logging
	{
	public:
		Logging();
		~Logging();

		static void Init();
		static void Release();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; };

	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};
}

#define GL_TRACE(...)    ::Gromit::Logging::GetLogger()->trace(__VA_ARGS__)
#define GL_INFO(...)     ::Gromit::Logging::GetLogger()->info(__VA_ARGS__)
#define GL_WARN(...)     ::Gromit::Logging::GetLogger()->warn(__VA_ARGS__)
#define GL_ERROR(...)    ::Gromit::Logging::GetLogger()->error(__VA_ARGS__)
