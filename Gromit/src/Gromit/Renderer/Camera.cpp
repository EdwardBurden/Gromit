#include "Camera.h"

namespace Gromit {
	glm::mat4 Camera::GetViewPrrojection()
	{
		return m_projectionMatrix * m_viewMatrix;
	}
}