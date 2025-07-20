#pragma once
#include "../Core.h"
#include "../RenderAPIs/RenderAPI.h"
#include "../AssetManagement/AssetManager.h"
#include "../Math/Math.h"

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

		void Update();
		void SubmitTest(float vertices[]);
		void DrawTest();
	private:
		static RenderAPI* m_activeRender;
		static int vbo;
	};
}