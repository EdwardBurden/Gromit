#pragma once
#include "../RenderAPIs/Context.h"

namespace Gromit {
	enum class RenderAPIType {
		OpenGL = 0,
		DiurectX = 1,
		Vulkan = 2
	};


	class Renderer
	{
	public:
		void Initialise(RenderAPIType renderApiType);
		//Context* CreateContext();


		void UpdateContexts() {
		//for each context loop through and draw things for that context
			// multiple context can exist in a window
		
		}
	private:
		std::vector<Context> m_contexts;

		RenderAPIType m_apiSetting;
	};
}