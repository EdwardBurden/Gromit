#include "AssetManagement/Mesh/MeshAsset.h"
#include "AssetManagement/AssetDatabase.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace Gromit
{
	void ProcessMesh(aiMesh* mesh, Vertex* vertices, size_t& verticesSize, unsigned int* indices, size_t& indicesSize);
	glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);

	MeshMetaData::MeshMetaData(int guid, std::string assetPath, nlohmann::json data) : MetaData(guid, assetPath, data)
	{
		data.at("importSetting").get_to(m_importSetting);
		m_layout.clear();
		for (const auto& layoutElement : data["layout"])
		{
			auto dataType =	layoutElement.begin().value().get<ShaderDataType>();
			m_layout.emplace(layoutElement.begin().key(), dataType);
		}
	}

	MeshAsset::MeshAsset(std::shared_ptr<MeshMetaData> metaData) : Asset(metaData)
	{
		//can move some into cuistom import
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(metaData->GetAssetPath(), metaData->m_importSetting);

		if (nullptr == scene) {
			const char* errorString = importer.GetErrorString();
			std::cout << errorString << std::endl;
			return;
		}

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			GL_ERROR(importer.GetErrorString());
			return;
		}

		auto root = scene->mRootNode;
		auto child = root->mChildren[0];
		if (root->mNumChildren > 1)
		{
			GL_ERROR("One Mesh per model for now");
		}

		for (size_t i = 0; i < child->mNumMeshes; i++)
		{
			unsigned int meshIndex = child->mMeshes[i];
			aiMesh* mesh = scene->mMeshes[meshIndex];
			ProcessMesh(mesh, m_vertices, m_verticesSize, m_indices, m_indicesSize);
		}
		m_transformMatrix = ConvertMatrixToGLMFormat(root->mTransformation);

		m_bufferLayout.clear();
		for (const auto& [key, value] : metaData->m_layout)
		{
			BufferLayoutElement e = BufferLayoutElement(value, key.c_str());
			m_bufferLayout.push_back(e);
		}
	}

	void ProcessMesh(aiMesh* mesh, Vertex* vertices, size_t& verticesSize, unsigned int* indices, size_t& indicesSize)
	{
		int vertIndex = 0;
		int indicesIndex = 0;
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 position, normal;
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;
			vertex.Position = position;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			vertex.Normal = normal;

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices[vertIndex] = vertex;
			vertIndex++;
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices[indicesIndex] = face.mIndices[j];
				indicesIndex++;
			}
		}

		verticesSize = vertIndex;
		indicesSize = indicesIndex;
	}

	glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}

	REGISTER_ASSET_HANDLER(MeshAssetHandler, AssetType::Mesh, MeshAsset, MeshMetaData, 8);
}