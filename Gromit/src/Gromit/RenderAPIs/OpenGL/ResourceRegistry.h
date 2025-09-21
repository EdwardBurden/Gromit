#pragma once
#include "OpenGL_Texture.h"
#include "OpenGL_Shader.h"

namespace Gromit::OpenGL {
	class ResourceRegistry
	{
	public:
		static inline std::unordered_map<int, OpenGL_Texture*> Textures;
		static inline std::unordered_map<int, OpenGL_Shader*> Shaders;
	};
}