#include "Windows_Window.h"


namespace Gromit {

	void WindowResize(GLFWwindow* window, int height, int width);
	void ViewportResize(GLFWwindow* window, int height, int width);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void window_refresh_callback(GLFWwindow* window);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

		glfwSetWindowUserPointer(m_window, this);
		glViewport(x, y, width, height);
		GL_INFO("Window Created");
		m_close = false;
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetWindowSizeCallback(m_window, WindowResize);
		glfwSetWindowRefreshCallback(m_window, window_refresh_callback);
		glfwSetFramebufferSizeCallback(m_window, ViewportResize);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	}

	void Windows_Window::UpdateWindow()
	{
		if (m_window == nullptr || m_close)
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
	void Windows_Window::Close() {
		glfwSetWindowShouldClose(m_window, GL_TRUE);
	}

	void WindowResize(GLFWwindow* window, int width, int height) {
		Windows_Window* thisWindow = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
		//TRIG_EVENT(WindowsResizeEvent, height, width);
	}

	void window_refresh_callback(GLFWwindow* window)
	{
		//draw_editor_ui(window);
		glfwSwapBuffers(window);
	}

	void ViewportResize(GLFWwindow* window, int width, int height) {
		Windows_Window* thisWindow = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
		TRIG_EVENT(WindowsResizeEvent, height, width);
	}


	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			Windows_Window* thisWindow = static_cast<Windows_Window*>(glfwGetWindowUserPointer(window));
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
