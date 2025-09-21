#pragma once
#include <json.hpp>

namespace Gromit
{
	enum class AssetType
	{
		None = -1,
		Texture = 0,
		Shader = 1,
		Material = 2,
		Mesh = 3,
		Entity = 4
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(AssetType,
		{
			{ AssetType::Texture, "Texture"},
			{ AssetType::Shader, "Shader" },
			{ AssetType::Material, "Material" },
			{ AssetType::Mesh, "Mesh" },
			{ AssetType::Entity, "Entity" }
		});


	struct AssetDependency
	{
		AssetType type;
		int guid;
	};


	struct MetaData
	{
	public:	
		int m_guid;
		MetaData(int guid, nlohmann::json data)
		{
			data.at("guid").get_to(m_guid);
			data.at("name").get_to(m_name);
			data.at("path").get_to(m_path);
			data.at("type").get_to(m_assetType);
		}

		std::string GetName() const { return m_name; }
		AssetType GetAssetType() const { return m_assetType; }


		std::vector<AssetDependency> GetDependencies() const { return m_dependencies; }
	protected:
	
		std::string m_name;
		std::string m_path;
		AssetType m_assetType;

		void AddDependency(AssetType type, int guid)
		{
			m_dependencies.push_back(AssetDependency(type, guid));
		}

	private:
		std::vector<AssetDependency> m_dependencies;
	};
}