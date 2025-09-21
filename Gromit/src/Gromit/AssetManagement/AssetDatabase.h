// asset databasse has a number of pools of assets. when assets that require other assets are loaded it should find them here or listen to when they are loaded to fill their own ref. 
// or maybe each asset just points here if they depend on another. will get thst sorted later

//asset pool
//each asset pool cointians a map of guid to unique ptr to the asset


#pragma once
#include "AssetManagement/PoolAllocator.h"
#include "AssetManagement/MeshAsset.h"
#include "AssetManagement/MeshMetaData.h"
#include "AssetManagement/TextureAsset.h"
#include "AssetManagement/TextureMetaData.h"
#include "AssetManagement/ShaderAsset.h"
#include "AssetManagement/ShaderMetaData.h"
#include "AssetManagement/MaterialAsset.h"
#include "AssetManagement/MaterialMetaData.h"

#include <json.hpp>

namespace Gromit
{
	class AssetDatabase
	{
	public:
		struct AssetRecord
		{
			MetaData* metaData;
			Asset* asset = nullptr;
			int refCount = 0; //actual asset uses not metadata
			bool permanent = false;

			AssetRecord(MetaData* meta)
			{
				metaData = meta;
			}
		};

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


		template<typename T>
		AssetRecord* GetMetadata(int guid)
		{
			return m_assetRegistry[guid];
		}

		template<typename T>
		AssetRecord* GetOrLoadMetadata(int guid, std::string name, nlohmann::json data)
		{
			if (!m_assetRegistry.contains(guid))
			{
				using Meta = typename T::MetaType;
				Meta* metaData = GetPool<Meta>().Allocate(guid, name, data);
				AssetRecord* record = new AssetRecord(metaData);
				m_assetRegistry[guid] = record;
			}
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
		struct PoolTraits;

		// Specializations
		template<> struct PoolTraits<MeshMetaData> { static constexpr size_t Capacity = 8; };
		template<> struct PoolTraits<MeshAsset> { static constexpr size_t Capacity = 8; };

		template<> struct PoolTraits<TextureMetaData> { static constexpr size_t Capacity = 8; };
		template<> struct PoolTraits<TextureAsset> { static constexpr size_t Capacity = 8; };

		template<> struct PoolTraits<ShaderMetaData> { static constexpr size_t Capacity = 8; };
		template<> struct PoolTraits<ShaderAsset> { static constexpr size_t Capacity = 8; };


		template<> struct PoolTraits<MaterialMetaData> { static constexpr size_t Capacity = 8; };
		template<> struct PoolTraits<MaterialAsset> { static constexpr size_t Capacity = 8; };

		template<typename T>
		using PoolFor = PoolAllocator<T, PoolTraits<T>::Capacity>;
		PoolFor<MeshMetaData> m_meshMetaDataPool;
		PoolFor<MeshAsset> m_meshAssetPool;

		PoolFor<TextureMetaData> m_textureMetaDataPool;
		PoolFor<TextureAsset> m_textureAssetPool;

		PoolFor<ShaderMetaData> m_shaderMetaDataPool;
		PoolFor<ShaderAsset> m_shaderAssetPool;

		PoolFor<MaterialMetaData> m_materialMetaDataPool;
		PoolFor<MaterialAsset> m_materialAssetPool;

		template<typename T>
		PoolFor<T>& GetPool();
		template<>PoolFor<MeshMetaData>& GetPool<MeshMetaData>() { return m_meshMetaDataPool; }
		template<>PoolFor<MeshAsset>& GetPool<MeshAsset>() { return m_meshAssetPool; }

		template<>PoolFor<TextureMetaData>& GetPool<TextureMetaData>() { return m_textureMetaDataPool; }
		template<>PoolFor<TextureAsset>& GetPool<TextureAsset>() { return m_textureAssetPool; }

		template<>PoolFor<ShaderMetaData>& GetPool<ShaderMetaData>() { return m_shaderMetaDataPool; }
		template<>PoolFor<ShaderAsset>& GetPool<ShaderAsset>() { return m_shaderAssetPool; }

		template<>PoolFor<MaterialMetaData>& GetPool<MaterialMetaData>() { return m_materialMetaDataPool; }
		template<>PoolFor<MaterialAsset>& GetPool<MaterialAsset>() { return m_materialAssetPool; }
	};
}
