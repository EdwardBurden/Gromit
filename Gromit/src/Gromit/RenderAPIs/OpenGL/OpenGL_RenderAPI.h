#pragma once
#include "../RenderAPI.h"
#include "../../Logging/Logging.h"
#include "OpenGL_Window.h"
#include "OpenGL_Shader.h"
#include "OpenGL_VertexBuffer.h"
#include "OpenGL_IndexBuffer.h"


namespace Gromit::OpenGL
{
	class OpenGL_RenderAPI : public RenderAPI
	{
	public:
		void Temp() override;
		void SetGlobalContext() override;
		void InitWindows() override;
		void TerminateWindows() override;
		Window* CreateWindow(int x, int y, int width, int height, const char* title) override;
		Shader* CreateShader(std::string vertexPath, std::string fragmentPath) override;
		VertexBuffer* CreateVertexBuffer(float* vertices, uint32_t size) override;
		IndexBuffer* CreateIndexBuffer(uint32_t* indices, uint32_t size) override;
		static inline GLFWwindow* SharedContext = nullptr;
		void Update() override;
	private:
		unsigned int m_vertexArray, m_indexBuffer; //temp
		Shader* m_tempShader;
		VertexBuffer* m_tempVB;
		IndexBuffer* m_tempIB;
	};
}