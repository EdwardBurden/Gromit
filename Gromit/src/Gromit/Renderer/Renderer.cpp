#include "Renderer.h"

//OpenGL
#include "../RenderAPIs/OpenGL/OpenGL_Context.h"
namespace Gromit {
	void Renderer::Initialise(RenderAPIType renderApiType)
	{
		m_apiSetting = renderApiType;

	}

	/*Context* Renderer::CreateContext()
	{
		if (m_apiSetting == RenderAPIType::OpenGL)
			return new  Gromit::OpenGL::OpenGL_Context();
		return nullptr;
	}*/
}