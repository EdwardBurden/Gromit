#include "OpenGL_RenderAPI.h"
#include "../../AssetManagement/AssetManager.h"

namespace Gromit::OpenGL
{
	void OnErrorCallback(int error, const char* description);

	void OpenGL_RenderAPI::InitWindows()
	{
		auto result = glfwInit();
		if (result)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwSetErrorCallback(OnErrorCallback);
			GL_INFO("GLFW Init Success");
		}
		else
		{
			GL_ERROR("Failed to Init GLFW");
		}
		return;
	}

	void OpenGL_RenderAPI::TerminateWindows()
	{
		glfwTerminate();
		GL_INFO("GLFW Release Success");
	}

	Window* OpenGL_RenderAPI::CreateWindow(int x, int y, int width, int height, const char* title)
	{
		auto badCode = static_cast<OpenGL_Context*>(Context::SharedContext);
		OpenGL_Window* wPtr = badCode->GetShared();
		GLFWwindow* window = nullptr;
		if (wPtr != nullptr)
		{
			window = wPtr->m_window;
		}

		auto newWindow = new OpenGL_Window(x, y, width, height, title, window);
		badCode->AddWindow(newWindow);
		return newWindow;
	}

	Shader* OpenGL_RenderAPI::CreateShader(const ShaderAsset& vert, const ShaderAsset& frag)
	{
		return new OpenGL_Shader(vert, frag);
	}

	VertexBuffer* OpenGL_RenderAPI::CreateVertexBuffer(float* vertices, uint32_t size)
	{
		return new OpenGL_VertexBuffer(vertices, size);
	}

	IndexBuffer* OpenGL_RenderAPI::CreateIndexBuffer(uint32_t* indices, uint32_t size)
	{
		return new OpenGL_IndexBuffer(indices, size);
	}

	VertexArray* OpenGL_RenderAPI::CreateVertexArray()
	{
		return new OpenGL_VertexArray();
	}

	BufferLayout* OpenGL_RenderAPI::CreateBufferLayout(std::initializer_list<Gromit::BufferLayoutElement> init)
	{
		return new OpenGL_BufferLayout(init);
	}

	Context* OpenGL_RenderAPI::CreateContext()
	{
		return new OpenGL_Context();
	}

	void OpenGL_RenderAPI::DrawIndexes(int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	}

	void OnErrorCallback(int error, const char* description)
	{
		GL_ERROR(error + description);
	}
}
