#pragma once
#include "../Core.h"
#include "../RenderAPIs/RenderAPI.h"

namespace Gromit {
	enum class RenderAPIType {
		OpenGL = 0,
		DiurectX = 1,
		Vulkan = 2
	};


	class GROMIT_API Renderer
	{
	public:
		static void SetAPI(RenderAPIType renderApiType);
		static RenderAPI* GetAPI();
	private:
		static RenderAPI* m_activeRender;
	};
}