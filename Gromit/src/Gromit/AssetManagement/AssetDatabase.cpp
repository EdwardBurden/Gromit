#include "AssetManagement/AssetDatabase.h"

namespace Gromit
{
	void AssetDatabase::RegisterHandler(AssetType type, IAssetHandler* handler)
	{
		GetHandlerRegistry()[type] = handler; //HERE
		std::cout << "Handler registered for type: " << (int)type << "\n";
	}

	AssetType AssetDatabase::FindAssetType(int guid)
	{
		auto it = m_assetRegistry.find(guid);
		if (it == m_assetRegistry.end())
			return AssetType::None;

		return m_assetRegistry[guid].m_metaData->GetAssetType();
	}

	void AssetDatabase::UnloadAsset(int guid, AssetType type)
	{
		auto it = GetHandlerRegistry().find(type);
		if (it == GetHandlerRegistry().end())
			return;


		it->second->UnLoadAsset(m_assetRegistry, guid);
	}

	std::shared_ptr<Asset> AssetDatabase::LoadAsset(int guid, AssetType type)
	{
		auto it = GetHandlerRegistry().find(type);
		if (it == GetHandlerRegistry().end())
			return nullptr;

		return it->second->LoadAsset(m_assetRegistry, guid);
	}

	void AssetDatabase::LoadMetadata(int guid, AssetType type, const std::string& name, const nlohmann::json& data)
	{
		auto it = GetHandlerRegistry().find(type);
		if (it != GetHandlerRegistry().end())
			it->second->LoadMetadata(m_assetRegistry, guid, name, data);
	}

	std::unordered_map<AssetType, IAssetHandler*>& AssetDatabase::GetHandlerRegistry()
	{
		static std::unordered_map<AssetType, IAssetHandler*> registry;
		return registry; // guaranteed initialized on first use
	}

	std::vector<AssetDependency> AssetDatabase::GetDependencies(int guid)
	{
		auto it = m_assetRegistry.find(guid);
		if (it == m_assetRegistry.end())
			return {};

		return m_assetRegistry[guid].m_metaData->GetDependencies();
	}
}