#include "FrameTime.h"
#include "RenderAPIs/OpenGL/OpenGL.h" //temp

namespace Gromit {

	float FrameTime::DeltaTime = 0.0f;
	float FrameTime::m_lastFrameTime = 0.0f;

	void FrameTime::SetDelta()
	{
		float time = glfwGetTime();
		DeltaTime = time - m_lastFrameTime;
	}
}