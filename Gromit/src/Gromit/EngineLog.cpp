#include "EngineLog.h"
#include "spdlog/spdlog.h"

namespace Gromit {

	EngineLog::EngineLog() {

	}

	EngineLog::~EngineLog() {

	}

	void EngineLog::LogName() {
	
		spdlog::info("Welcome to spdlog!");
	}
}