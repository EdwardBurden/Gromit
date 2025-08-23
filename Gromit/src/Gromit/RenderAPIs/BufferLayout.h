#pragma once

#include <initializer_list>
#include <map>
#include <glad/glad.h> 

enum class ShaderDataType
{
	None = 0,
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
	BufferLayout(std::initializer_list<BufferLayoutElement> init) : data(init)
	{
		stride = 0;
		for (size_t i = 0; i < data.size(); i++)
		{
			GLsizei size = (GLsizei)data[i].m_shaderDataType;
			stride += size;
		}
	}
	~BufferLayout() {}

	inline void SetAttributes()
	{
		int offset = 0;
		for (size_t i = 0; i < data.size(); i++)
		{
			//data
			glEnableVertexAttribArray(i);
			const auto& type = data[i].m_shaderDataType;
			GLsizei size = (GLsizei)type;
			glVertexAttribPointer(i, ShaderDataTypeToComponentSize(type), ShaderDataTypeToEnum(type), GL_FALSE, stride, (void*)offset); //todo add normalise switch
			offset += size;
		}
	}

	inline GLint ShaderDataTypeToComponentSize(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float3: return 3;
		case ShaderDataType::Float4: return 4;
			return 0;
		}
	}

	inline GLenum ShaderDataTypeToEnum(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
			return 0;
		}
	}

private:
	std::vector<BufferLayoutElement> data;
	int stride;
};