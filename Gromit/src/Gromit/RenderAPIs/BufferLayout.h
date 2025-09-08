#pragma once

namespace Gromit
{
	enum class ShaderDataType
	{
		None = 0,
		Float2 = sizeof(float) * 2,
		Float3 = sizeof(float) * 3,
		Float4 = sizeof(float) * 4,
	};

	struct BufferLayoutElement
	{
		const ShaderDataType m_shaderDataType;
		const char* m_title;
		BufferLayoutElement(const ShaderDataType& shaderDataType, const char* title)
			: m_shaderDataType(shaderDataType), m_title(title)
		{
		}
	};

	class BufferLayout //todo needs moving into opengl namespace with virtual base
	{
	public:

		~BufferLayout() {}

		virtual void SetStride() = 0;
		virtual void SetAttributes() = 0;

	protected:
	};

}