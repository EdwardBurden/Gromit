#include "Windows_Window.h"


namespace Gromit {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	Windows_Window::Windows_Window(int x, int y, int width, int height, const char* title)
	{
		m_window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (m_window == NULL)
		{
			GL_ERROR("Failed to create GLFW window");
			return;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowPos(m_window, x, y);
		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (version != 1)
		{
			Gromit::Logging::GetLogger()->error("Failed to initialize GLAD");
			return;
		}
		m_x = x;
		m_y = y;
		m_height = height;
		m_width = width;
		glfwSetKeyCallback(m_window, key_callback);
		GL_INFO("Window Created");
		m_close = false;
	}

	void Windows_Window::UpdateWindow()
	{
		if (m_window == nullptr)
			return;

		if (glfwWindowShouldClose(m_window)) {
			//hhandle
			glfwDestroyWindow(m_window); //todo and add remove ourselvess from list
			m_window = nullptr;
			m_close = true;
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_window);

	}


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
