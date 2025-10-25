#pragma once
#include <json.hpp>

namespace Gromit
{
	enum class AssetType
	{
		None,
		Texture,
		Shader,
		Material,
		Mesh,
		Entity,
		Scene
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(AssetType,
		{
			{ AssetType::None, "None"},
			{ AssetType::Texture, "Texture"},
			{ AssetType::Shader, "Shader" },
			{ AssetType::Material, "Material" },
			{ AssetType::Mesh, "Mesh" },
			{ AssetType::Entity, "Entity" },
			{ AssetType::Scene, "Scene"},
		});


	struct AssetDependency
	{
		AssetType type;
		int guid;
	};


	struct MetaData
	{
	public:
		MetaData(int guid, std::string assetPath, nlohmann::json data)
		{
			m_guid = guid;
			data.at("name").get_to(m_name);
			data.at("path").get_to(m_path);
			data.at("type").get_to(m_assetType);
			m_assetPath = assetPath + m_path;
		}

		int GetGUID() const { return m_guid; }
		std::string GetAssetPath() const { return m_assetPath; }
		std::string GetName() const { return m_name; }
		AssetType GetAssetType() const { return m_assetType; }
		std::vector<AssetDependency> GetDependencies() const { return m_dependencies; }
		inline void AddDependency(AssetType type, int guid) { m_dependencies.push_back(AssetDependency(type, guid)); }
	protected:
		int m_guid;
		std::string m_name;
		std::string m_path;
		AssetType m_assetType;
		std::string m_assetPath;
	private:
		std::vector<AssetDependency> m_dependencies;
	};
}