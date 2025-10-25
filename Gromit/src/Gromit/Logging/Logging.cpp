#pragma once
#include "Logging.h"

namespace Gromit 
{
	std::shared_ptr<spdlog::logger> Logging::s_logger;

	Logging::Logging()
	{
		std::cout << "Logging Constructor" << std::endl;
		s_logger = spdlog::stdout_color_mt("console");
	}

	void Logging::OnStartUp()
	{
		//s_logger = spdlog::stdout_color_mt("console");
	}

	void Logging::OnShutDown()
	{
		s_logger.reset();
	}

	bool Logging::OnUpdate()
	{
		return false;
	}
}