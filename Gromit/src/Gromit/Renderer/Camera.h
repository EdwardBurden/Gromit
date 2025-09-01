#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Gromit
{
	class Camera
	{
	public:
		Camera(float fovAngle, float aspect, float near = 0.05f, float far = 500.0f)
		{
			m_position = glm::vec3(0);
			m_up = glm::normalize(glm::vec3(0, 1, 0));
			m_forward = glm::normalize(glm::vec3(0, 0, -1));
			m_projectionMatrix = glm::perspective(glm::radians(fovAngle), aspect, near, far); // 
			m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
		}

		glm::mat4 GetViewPrrojection();
	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_up;
	};
}