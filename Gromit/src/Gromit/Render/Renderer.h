#pragma once
#include "Core.h"
#include "RenderAPIs/RenderAPI.h"
#include "AssetManagement/AssetManager.h"
#include "RenderObject.h"
#include "Camera.h"
#include "Math/Math.h"
#include "EntityManagement/SceneManager.h"

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
		void OnUpdate(const SceneInstance& sceneInstance);
		void AddDrawObject(RenderObject* obj);
		void DrawRenderObject(RenderObject* obj, Camera* camera, float update);
		void SetAPI(RenderAPIType renderApiType);
		static  RenderAPI* GetAPI() { return m_activeRender; }
		void OnStartUp() override;
		void OnShutDown() override;
	private:
		static RenderAPI* m_activeRender;
		Camera* camera;
		float update;
		std::unordered_map<int, RenderObject*> tempRenderList;
		BufferLayout* m_tempBuffer;
	};
}