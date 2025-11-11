#pragma once
#include "Math/Math.h"
#include "AssetManagement/Asset.h"

namespace Gromit
{

	enum class ShaderDataType
	{
		None = 0,
		Float2 = sizeof(float) * 2,
		Float3 = sizeof(float) * 3,
		Float4 = sizeof(float) * 4,
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(ShaderDataType, {
		{ ShaderDataType::None, "None" },
		{ ShaderDataType::Float2, "Float2" },
		{ ShaderDataType::Float3, "Float3" },
		{ ShaderDataType::Float4, "Float4" }
		});

	struct BufferLayoutElement
	{
		const ShaderDataType m_shaderDataType;
		const char* m_title;
		BufferLayoutElement(const ShaderDataType& shaderDataType, const char* title)
			: m_shaderDataType(shaderDataType), m_title(title)
		{
		}
	};

	struct MeshMetaData : public MetaData
	{
	public:
		MeshMetaData(int guid, std::string assetPath, nlohmann::json data);
		int m_importSetting;
		std::unordered_map<std::string, ShaderDataType> m_layout;
	};

	struct MeshAsset : public Asset
	{
	public:
		MeshAsset(std::shared_ptr<MeshMetaData> metaData);
		const Vertex* GetVertices() const { return m_vertices; }
		const size_t GetVertexCount() const { return m_verticesSize; }
		const unsigned int* GetIndices() const { return m_indices; }
		const size_t GetIndexCount() const { return m_indicesSize; }
		const std::vector<BufferLayoutElement>& GetLayout() const { return m_bufferLayout; }
	private:
		static constexpr size_t MAX_VERTICES = 100; //todo look into pool here too?
		static constexpr size_t MAX_INDICES = 500;

		Vertex m_vertices[MAX_VERTICES]; //todo be stack
		unsigned int m_indices[MAX_INDICES];
		glm::mat4 m_transformMatrix;

		size_t m_verticesSize;
		size_t m_indicesSize;

		std::vector<BufferLayoutElement> m_bufferLayout;

	};
}