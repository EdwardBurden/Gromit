// asset databasse has a number of pools of assets. when assets that require other assets are loaded it should find them here or listen to when they are loaded to fill their own ref. 
// or maybe each asset just points here if they depend on another. will get thst sorted later

//asset pool
//each asset pool cointians a map of guid to unique ptr to the asset


#pragma once
#include "AssetManagement/PoolAllocator.h"
#include "AssetManagement/MeshAsset.h"
#include "AssetManagement/MeshMetaData.h"
#include <json.hpp>

namespace Gromit
{
	class AssetDatabase
	{
	public:
		struct AssetRecord
		{
			MetaData* metaData;
			AssetNew* asset = nullptr;
			int refCount = 0; //actual asset uses not metadata
			bool permanent = false;

			AssetRecord(MetaData* meta)
			{
				metaData = meta;
			}
		};

		AssetDatabase() {};

		template<typename T>
		AssetRecord* GetOrLoadMetadata(int guid, std::string name, nlohmann::json data)
		{
			if (m_assetRegistry.contains(guid))
			{
				return m_assetRegistry[guid];
			}

			using Meta = typename T::MetaType;
			Meta* metaData = GetPool<Meta>().Allocate(guid, name, data);
			AssetRecord* record = new AssetRecord(metaData);
			m_assetRegistry[guid] = record;
			return m_assetRegistry[guid];
		}

		template<typename T>
		void UnloadMetaData(int guid)
		{
			if (m_assetRegistry.contains(guid))
			{
				using Meta = typename T::MetaType;
				GetPool<Meta>().Free(m_assetRegistry[guid]->metaData);
				delete m_assetRegistry[guid];
				m_assetRegistry.erase(guid);
			}
		}

		template<typename T>
		T* GetOrLoadAsset(int guid)
		{
			if (!m_assetRegistry.contains(guid))
			{
				//erro for now
				return nullptr;
			}

			// new load example
			AssetRecord* record = m_assetRegistry[guid];
			if (record->asset == nullptr || record->refCount == 0)
			{

				auto thing = static_cast<typename T::MetaType*>(record->metaData);
				T* mesh = GetPool<T>().Allocate(thing);
				record->asset = mesh;
			}

			record->refCount++;
			T* derivedPtr = static_cast<T*>(record->asset);

			return derivedPtr;
		}

		template<typename T>
		void UnloadAsset(int guid)
		{
			if (!m_assetRegistry.contains(guid))
			{
				return;
			}
			AssetRecord* record = m_assetRegistry[guid];
			record->refCount--;

			if (!record->permanent && record->refCount <= 0)
			{
				GetPool<T>().Free(m_assetRegistry[guid]->asset);
			}
		}
		
	private:
		std::unordered_map<int, AssetRecord*> m_assetRegistry;

		template<typename T>
		using PoolFor = PoolAllocator<T, T::PoolCapacity>;
		PoolFor<MeshMetaData> m_meshMetaDataPool;
		PoolFor<MeshAsset> m_meshAssetPool;

		template<typename T>
		PoolFor<T>& GetPool();

		template<> 
		PoolFor<MeshMetaData>& GetPool<MeshMetaData>() { return m_meshMetaDataPool; }
		template<> 
		PoolFor<MeshAsset>& GetPool<MeshAsset>() { return m_meshAssetPool; }
	};
}
