#pragma once
#include "Core.h"
#include "EventSystem/EventSystem.h"

namespace Gromit {

	class GROMIT_API Application {
	public:
		Application();
		virtual ~Application();

		void StartUp();
	};
}