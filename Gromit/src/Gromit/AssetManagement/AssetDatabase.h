// asset databasse has a number of pools of assets. when assets that require other assets are loaded it should find them here or listen to when they are loaded to fill their own ref. 
// or maybe each asset just points here if they depend on another. will get thst sorted later

//asset pool
//each asset pool cointians a map of guid to unique ptr to the asset


#pragma once
#include "AssetManagement/AssetRecord.h"
#include "Core/PoolAllocator.h"
#include <json.hpp>
#include <memory>
#include <unordered_map>

namespace Gromit
{
	class IAssetHandler
	{
	public:
		virtual void LoadMetadata(std::unordered_map<int, AssetRecord>& registry, int guid, const std::string&, const nlohmann::json&) = 0;
		virtual void UnloadMetaData(std::unordered_map<int, AssetRecord>& registry, int guid) = 0;
		virtual std::shared_ptr<Asset> LoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) = 0;
		virtual void UnLoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) = 0;
	};


	template<typename TAsset, typename TMeta, size_t Poolsize = 64>
	class AssetHandler : public IAssetHandler
	{
	public:
		void LoadMetadata(std::unordered_map<int, AssetRecord>& registry, int guid, const std::string& path, const nlohmann::json& data) override
		{
			if (!registry.contains(guid))
			{
				TMeta* meta = m_metaPool.Allocate(guid, path, data);
				std::cout << "Allocated MetaData: " << meta->GetName() << "\n";
				auto ptr = std::shared_ptr<TMeta>(meta, [this](TMeta* a)
					{
						std::cout << "MetaData Freed: " << a->GetName() << "\n";
						m_metaPool.Free(a); // return to pool
					});
				registry.emplace(guid, AssetRecord(ptr)); //set if permanant here from parameters

			}
			std::cout << "Loaded Called for metadata guid: " << guid << "\n";
		}

		virtual void UnloadMetaData(std::unordered_map<int, AssetRecord>& registry, int guid) override
		{
			auto it = registry.find(guid);
			if (it == registry.end())
				return;

			AssetRecord& record = it->second;
			if (!record.m_metaData)
				return;

			if (!record.m_permanent && record.m_metaData.use_count() == 1)
			{
				record.m_metaData.reset();
			}
		}

		std::shared_ptr<Asset> LoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) override
		{
			auto it = registry.find(guid);
			if (it == registry.end())
				return nullptr;

			AssetRecord& record = it->second;
			if (!record.m_asset)
			{
				std::shared_ptr<TMeta> meta = std::static_pointer_cast<TMeta>(record.m_metaData);
				TAsset* asset = m_assetPool.Allocate(meta);
				std::cout << "Allocated Asset: " << meta->GetName() << "\n";
				record.m_asset = std::shared_ptr<TAsset>(asset, [this](TAsset* a)
					{
						std::cout << "Asset Freed: " << a->GetMeta<TMeta>()->GetName() << "\n";
						m_assetPool.Free(a); // return to pool
					});
			}
			std::cout << "Load Called for Asset: " << record.m_metaData->GetName() << "\n";
			return record.m_asset;
		}

		void UnLoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) override
		{
			auto it = registry.find(guid);
			if (it == registry.end())
				return;

			AssetRecord& record = it->second;
			if (!record.m_asset)
				return;

			std::cout << "Refs for Asset: " << record.m_metaData->GetName() << " = " << record.m_asset.use_count() << "\n";
			if (!record.m_permanent && record.m_asset.use_count() == 1)
			{
				record.m_asset.reset();
			}
		}
	private:

		PoolAllocator<TMeta, Poolsize> m_metaPool;
		PoolAllocator<TAsset, Poolsize> m_assetPool;
	};

	class AssetDatabase
	{
	public:
		AssetDatabase() = default;
		static void RegisterHandler(AssetType type, IAssetHandler* handler);
		AssetType FindAssetType(int guid);
		std::vector<AssetDependency> GetDependencies(int guid);
		void LoadMetadata(int guid, AssetType type, const std::string& name, const nlohmann::json& data);
		void UnLoadMetadata(int guid, AssetType type);
		std::shared_ptr<Asset> LoadAsset(int guid, AssetType type);
		void UnloadAsset(int guid, AssetType type);

	private:
		std::unordered_map<int, AssetRecord> m_assetRegistry;
		static std::unordered_map<AssetType, IAssetHandler*>& GetHandlerRegistry();
	};


#define REGISTER_ASSET_HANDLER(HANDLER_CLASS, TYPE, ASSET, META, POOL_SIZE) \
class HANDLER_CLASS : public AssetHandler<ASSET, META, POOL_SIZE> \
{ \
public: \
    HANDLER_CLASS() { AssetDatabase::RegisterHandler(TYPE, this); } \
}; \
static HANDLER_CLASS s_##HANDLER_CLASS
}
