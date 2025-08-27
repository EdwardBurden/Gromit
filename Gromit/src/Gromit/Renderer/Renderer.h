#pragma once
#include "../Core.h"
#include "../RenderAPIs/RenderAPI.h"
#include "../AssetManagement/AssetManager.h"

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

		//static void PreScene();
		//static void Submit(VertexArray* va);
		//static void PostScene();

		void SetAPI(RenderAPIType renderApiType);
		static  RenderAPI* GetAPI() { return m_activeRender; }
		void OnStartUp() override;
		void OnShutDown() override;
	private:
		static RenderAPI* m_activeRender;
	};
}