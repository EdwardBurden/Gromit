#pragma once
#include "../Core.h"
#include "../RenderAPIs/RenderAPI.h"
#include "../AssetManagement/AssetManager.h"
#include "../Math/Math.h"

namespace Gromit 
{
	enum class RenderAPIType 
	{
		OpenGL = 0,
		DiurectX = 1,
		Vulkan = 2
	};

	class GROMIT_API Renderer : public IEngineService
	{
	public:
		Renderer()
		{
			std::cout << "Renderer Constructor" << std::endl;
		}

		void SetAPI(RenderAPIType renderApiType);
		RenderAPI* GetAPI();

		void Temp();
		void SetGlobalContext();
		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();
	private:
		RenderAPI* m_activeRender;
	};
}