// asset databasse has a number of pools of assets. when assets that require other assets are loaded it should find them here or listen to when they are loaded to fill their own ref. 
// or maybe each asset just points here if they depend on another. will get thst sorted later

//asset pool
//each asset pool cointians a map of guid to unique ptr to the asset


#pragma once
#include "AssetManagement/AssetRecord.h"
#include "AssetManagement/PoolAllocator.h"
#include "Logging/Logging.h"
#include <json.hpp>
#include <memory>

namespace Gromit
{
	class  IAssetHandler
	{
	public:
		virtual ~IAssetHandler() = default;
		virtual void LoadMetadata(std::unordered_map<int, AssetRecord*>&, int guid, const std::string&, const nlohmann::json&) = 0;
		virtual Asset* LoadAsset(std::unordered_map<int, AssetRecord*>&, int guid) = 0;
	};


	template<typename TAsset, typename TMeta, size_t Poolsize = 64>
	class AssetHandler : public IAssetHandler
	{
	public:
		void LoadMetadata(std::unordered_map<int, AssetRecord*>& registry, int guid, const std::string& name, const nlohmann::json& data) override
		{
			if (!registry.contains(guid))
			{
				TMeta* meta = m_metaPool.Allocate(guid, name, data);	
				AssetRecord* record = new AssetRecord(meta);
				registry[guid] = record;
				std::cout << "Loaded metadata: " << meta->GetName() << "\n";
			}
		}

		Asset* LoadAsset(std::unordered_map<int, AssetRecord*>& registry, int guid) override
		{
			auto it = registry.find(guid);
			if (it == registry.end())
				return nullptr;

			AssetRecord* record = it->second;
			if (!record->asset)
			{
				TMeta* meta = static_cast<TMeta*>(record->metaData);
				TAsset* asset = m_assetPool.Allocate(meta);
				record->asset = asset;
			}

			record->refCount++;
			return record->asset;
		}

	private:

		PoolAllocator<TMeta, Poolsize> m_metaPool;
		PoolAllocator<TAsset, Poolsize> m_assetPool;
	};


#define REGISTER_ASSET_HANDLER(HANDLER_CLASS, TYPE, ASSET, META, POOL_SIZE) \
class HANDLER_CLASS : public AssetHandler<ASSET, META, POOL_SIZE> \
{ \
public: \
    HANDLER_CLASS() { AssetDatabase::RegisterHandler(TYPE,this); } \
}; \
static HANDLER_CLASS s_##HANDLER_CLASS


	class AssetDatabase
	{
	public:

		static void RegisterHandler(AssetType type, IAssetHandler* handler)
		{
			s_handlerMap[type] = handler; //todo check already exists before adding
		}


		AssetDatabase() {};

		AssetType FindAssetType(int guid)
		{
			if (!m_assetRegistry.contains(guid))
			{
				//error 
				return AssetType::None;
			}
			return m_assetRegistry[guid]->metaData->GetAssetType();
		}

		std::vector<AssetDependency> GetDependencies(int guid)
		{
			return m_assetRegistry[guid]->metaData->GetDependencies();
		}

		Asset* LoadAsset(int guid, AssetType type)
		{
			auto it = s_handlerMap.find(type);
			if (it != s_handlerMap.end())
				return it->second->LoadAsset(m_assetRegistry, guid);
			return nullptr;
		}

		void LoadMetadata(int guid, AssetType type, const std::string& name, const nlohmann::json& data)
		{
			auto it = s_handlerMap.find(type);
			if (it != s_handlerMap.end())
				it->second->LoadMetadata(m_assetRegistry, guid, name, data);
		}


	private:
		std::unordered_map<int, AssetRecord*> m_assetRegistry;
		static inline std::unordered_map<AssetType, IAssetHandler*> s_handlerMap;
	};
}
