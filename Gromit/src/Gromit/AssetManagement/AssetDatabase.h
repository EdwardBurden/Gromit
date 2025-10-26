// asset databasse has a number of pools of assets. when assets that require other assets are loaded it should find them here or listen to when they are loaded to fill their own ref. 
// or maybe each asset just points here if they depend on another. will get thst sorted later

//asset pool
//each asset pool cointians a map of guid to unique ptr to the asset


#pragma once
#include "AssetManagement/AssetRecord.h"
#include "AssetManagement/PoolAllocator.h"
#include <json.hpp>
#include <memory>
#include <unordered_map>

namespace Gromit
{
	class IAssetHandler
	{
	public:
		virtual void LoadMetadata(std::unordered_map<int, AssetRecord>& registry, int guid, const std::string&, const nlohmann::json&) = 0;
		virtual std::shared_ptr<Asset> LoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) = 0;
		virtual void UnLoadAsset(std::unordered_map<int, AssetRecord>& registry, int guid) = 0;
	};


	template<typename TAsset, typename TMeta, size_t Poolsize = 64>
	class AssetHandler : public IAssetHandler
	{
	public:
		void LoadMetadata(std::unordered_map<int, AssetRecord>& registry, int guid, const std::string& name, const nlohmann::json& data) override
		{
			if (!registry.contains(guid))
			{
				TMeta* meta = m_metaPool.Allocate(guid, name, data);
				auto ptr = std::shared_ptr<TMeta>(meta, [this](TMeta* a)
					{
						m_metaPool.Free(a); // return to pool
					});

				registry.emplace(guid, AssetRecord(ptr)); //set if permanant here from parameters
				std::cout << "Loaded metadata: " << meta->GetName() << "\n";
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
				//	TMeta* meta = static_cast<TMeta*>(record.m_metaData);
				TAsset* asset = m_assetPool.Allocate(meta);
				record.m_asset = std::shared_ptr<TAsset>(asset, [this](TAsset* a)
					{
						m_assetPool.Free(a); // return to pool
					});
			}

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
		std::shared_ptr<Asset> LoadAsset(int guid, AssetType type);
		void UnloadAsset(int guid, AssetType type);
		void LoadMetadata(int guid, AssetType type, const std::string& name, const nlohmann::json& data);
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
