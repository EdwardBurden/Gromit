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
	void OpenGL_RenderAPI::Temp()
	{
		const auto& manager = ServiceLocator::GetService<AssetManager>();
		manager->LoadAsset(545);
		manager->LoadAsset(123434);
		ShaderAsset* vert = manager->GetAsset<ShaderAsset>(545);
		ShaderAsset* frag = manager->GetAsset<ShaderAsset>(123434);
		//	manager->LoadAsset(123434);
			//fs::path current = fs::current_path();


		//m_tempShader = CreateShader(manager->pathTemp + vert->path, manager->pathTemp + frag->path);

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 0.2f , 0.9f,  // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f , 0.9f, // bottom right
			-0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 1.2f , 0.9f, // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.2f , 0.9f, // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
	OpenGL_BufferLayout* layout = new OpenGL_BufferLayout
		{
			{ShaderDataType::Float3 , "position"},
			{ShaderDataType::Float4 , "color"}
		};
		m_tempShader = CreateShader(*vert, *frag);
		m_va = CreateVertexArray();
		m_va->Bind();
		auto m_tempVB = CreateVertexBuffer(vertices, sizeof(vertices));
		m_tempVB->SetLayout(layout);
		auto m_tempIB = CreateIndexBuffer(indices, sizeof(indices));
		m_va->SetIndexBuffer(m_tempIB);
		m_va->SetVertexBuffer(m_tempVB);
		m_tempVB->Unbind();
		m_va->Unbind();
	}

	void OpenGL_RenderAPI::SetGlobalContext()
	{
		/* glUseProgram(shaderProgram);
		 glBindBuffer(GL_ARRAY_BUFFER, VBO);
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		 glBindVertexArray(m_vertexArray);
		 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		 glEnableVertexAttribArray(0);*/
	}

	void OpenGL_RenderAPI::TerminateWindows()
	{
		glfwTerminate();
		GL_INFO("GLFW Release Success");
	}

	Window* OpenGL_RenderAPI::CreateWindow(int x, int y, int width, int height, const char* title)
	{
		Window* w = new OpenGL_Window(x, y, width, height, title);
		return w;
	}

	Shader* OpenGL_RenderAPI::CreateShader(const ShaderAsset& vert, const ShaderAsset& frag)
	{
		Shader* s = new OpenGL_Shader(vert, frag);
		return s;
	}

	VertexBuffer* OpenGL_RenderAPI::CreateVertexBuffer(float* vertices, uint32_t size)
	{
		VertexBuffer* vb = new OpenGL_VertexBuffer(vertices, size);
		return vb;
	}

	IndexBuffer* OpenGL_RenderAPI::CreateIndexBuffer(uint32_t* indices, uint32_t size)
	{
		IndexBuffer* vb = new OpenGL_IndexBuffer(indices, size);
		return vb;
	}

	VertexArray* OpenGL_RenderAPI::CreateVertexArray()
	{
		VertexArray* va = new OpenGL_VertexArray();
		return va;
	}

	void OpenGL_RenderAPI::Update()
	{
		m_tempShader->Bind();
		m_va->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		m_tempShader->Unbind();
		m_va->Unbind();
	}


	void OnErrorCallback(int error, const char* description)
	{
		GL_ERROR(error + description);
	}
}
