#include "OpenGL_Window.h"

namespace Gromit {
	namespace OpenGL {
		void WindowResize(GLFWwindow* window, int height, int width);
		void ViewportResize(GLFWwindow* window, int height, int width);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void window_refresh_callback(GLFWwindow* window);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		OpenGL_Window::OpenGL_Window(int x, int y, int width, int height, const char* title)
		{
			if (OpenGL_RenderAPI::SharedContext == nullptr) 
			{
				m_window = glfwCreateWindow(width, height, title, NULL, NULL);
				OpenGL_RenderAPI::SharedContext = m_window;
			}
			else 
			{
				m_window = glfwCreateWindow(width, height, title, NULL, OpenGL_RenderAPI::SharedContext);
			}
			if (m_window == NULL)
			{
				GL_ERROR("Failed to create GLFW window");
				return;
			}
			//m_context = new OpenGL_Context(m_window);
			//m_context->Init();
			glfwMakeContextCurrent(m_window);
			glfwSetWindowPos(m_window, x, y);
			int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			if (version != 1)
			{
				Gromit::Logging::GetLogger()->error("Failed to initialize GLAD");
				return;
			}
			GL_INFO((const char*)glGetString(GL_VENDOR));
			GL_INFO((const char*)glGetString(GL_RENDERER));
			GL_INFO((const char*)glGetString(GL_VERSION));
			m_x = x;
			m_y = y;
			m_height = height;
			m_width = width;

			glfwSetWindowUserPointer(m_window, this);
			glViewport(0, 0, m_width, m_height);
			GL_INFO("Window Created");
			m_close = false;
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetWindowSizeCallback(m_window, WindowResize);
			glfwSetWindowRefreshCallback(m_window, window_refresh_callback);
			glfwSetFramebufferSizeCallback(m_window, ViewportResize);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		}

		void OpenGL_Window::Activate()
		{
			glfwMakeContextCurrent(m_window);
		}

		void OpenGL_Window::PreUpdate()
		{	
			if (m_window == nullptr || m_close)
				return;

			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glfwMakeContextCurrent(m_window);
			glViewport(0, 0, m_width, m_height);
			glClearColor(0.002f * m_width, 0.003f* m_height, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void OpenGL_Window::PostUpdate()
		{
			if (m_window == nullptr || m_close)
				return;

			glfwSwapBuffers(m_window);
			glfwPollEvents();
			glfwMakeContextCurrent(NULL);

			if (glfwWindowShouldClose(m_window))
			{
				//hhandle
				glfwDestroyWindow(m_window); //todo and add remove ourselvess from list
				m_window = nullptr;
				m_close = true;
				return;
			}
		}


		void OpenGL_Window::Close() {
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		void WindowResize(GLFWwindow* window, int width, int height) {
			OpenGL_Window* thisWindow = static_cast<OpenGL_Window*>(glfwGetWindowUserPointer(window));
			thisWindow->m_width = width;
			thisWindow->m_height = height;
			//TRIG_EVENT(WindowsResizeEvent, height, width);
		}

		void window_refresh_callback(GLFWwindow* window)
		{
			//draw_editor_ui(window);
			glfwSwapBuffers(window);
		}

		void ViewportResize(GLFWwindow* window, int width, int height) 
		{
			OpenGL_Window* thisWindow = static_cast<OpenGL_Window*>(glfwGetWindowUserPointer(window));
			TRIG_EVENT(WindowsResizeEvent, height, width);
			thisWindow->m_width = width;
			thisWindow->m_height = height;
			glfwMakeContextCurrent(window);
			glViewport(0, 0, width, height);
			glfwMakeContextCurrent(nullptr);
		}


		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				OpenGL_Window* thisWindow = static_cast<OpenGL_Window*>(glfwGetWindowUserPointer(window));
				thisWindow->Close();
				//glfwSetWindowShouldClose(window, GL_TRUE);
			}
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
				TRIG_EVENT(MouseClickEvent, 1);
		}
	}
}