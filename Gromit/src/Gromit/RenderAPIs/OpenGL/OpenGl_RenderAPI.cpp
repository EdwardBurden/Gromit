#include "OpenGL_RenderAPI.h"
#include "../../AssetManagement/AssetManager.h"

namespace Gromit {
	namespace OpenGL {

		// GLFWwindow* OpenGL_RenderAPI::m_staticContext = nullptr;

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		unsigned int EBO;

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
			manager->LoadAsset(123434);
			//fs::path current = fs::current_path();

			m_tempShader = CreateShader(manager->pathTemp + vert->path, manager->pathTemp + frag->path);

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

			glGenVertexArrays(1, &m_vertexArray);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(m_vertexArray);

			m_tempVB = CreateVertexBuffer(vertices, sizeof(vertices));
			m_tempVB->Bind();
			m_tempIB = CreateIndexBuffer(indices, sizeof(indices));
			m_tempIB->Bind();

			BufferLayout layout = 
			{
				{ShaderDataType::Float3 , "position"},
				{ShaderDataType::Float4 , "color"}
			};
			layout.SetAttributes();
			//layout.Some
			//m_tempVB->SetLayout(layout);
			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//glEnableVertexAttribArray(0);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			m_tempVB->Unbind();
			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

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

		Shader* OpenGL_RenderAPI::CreateShader(std::string vertexPath, std::string fragmentPath)
		{
			Shader* s = new OpenGL_Shader(vertexPath, fragmentPath);
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

		void OpenGL_RenderAPI::Update()
		{
			m_tempShader->Bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			m_tempShader->Unbind();
		}


		void OnErrorCallback(int error, const char* description)
		{
			GL_ERROR(error + description);
		}

	}
}
