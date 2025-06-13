#pragma once
#include "../../Grom_pch.h"
#include "Logging.h"


namespace Gromit {

	std::shared_ptr<spdlog::logger> Logging::s_logger;

	void Logging::Init() {
		s_logger = spdlog::stdout_color_mt("console");
	}

	void Logging::Release() {
		//delete things
	}

}