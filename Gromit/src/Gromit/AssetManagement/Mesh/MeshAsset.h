#pragma once
#include "Math/Math.h"
#include "AssetManagement/Asset.h"

namespace Gromit
{
	struct MeshMetaData : public MetaData
	{
	public:
		MeshMetaData(int guid, std::string assetPath, nlohmann::json data);
		int m_importSetting;
	};

	struct MeshAsset : public Asset
	{
	public:
		MeshAsset(MeshMetaData* metaData);
		const Vertex* GetVertices() const { return m_vertices; }
		const size_t GetVertexCount() const { return m_verticesSize; }
		const unsigned int* GetIndices() const { return m_indices; }
		const size_t GetIndexCount() const { return m_indicesSize; }
	private:
		static constexpr size_t MAX_VERTICES = 100; //todo look into pool here too?
		static constexpr size_t MAX_INDICES = 500;

		Vertex m_vertices[MAX_VERTICES]; //todo be stack
		unsigned int m_indices[MAX_INDICES];
		glm::mat4 m_transformMatrix;

		size_t m_verticesSize;
		size_t m_indicesSize;
	};
}