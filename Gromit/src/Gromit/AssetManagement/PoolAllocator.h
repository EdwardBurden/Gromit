//maybe move later

#pragma once

namespace Gromit
{

	template<typename T>
	struct Chunk
	{
		alignas(T) unsigned char asset[sizeof(T)];
		Chunk* nextChunk;
	};

	template<typename T, size_t Capacity>
	class PoolAllocator
	{
	public:
		PoolAllocator()
		{
			for (size_t i = 0; i < Capacity - 1; i++)
			{
				m_pool[i].nextChunk = &m_pool[i + 1];
			}
			m_pool[Capacity - 1].nextChunk = nullptr;
			m_freePointer = &m_pool[0];
		}

		~PoolAllocator()
		{
			for (size_t i = 0; i < Capacity - 1; i++)
			{
				T* asset = reinterpret_cast<T*>(&m_pool[i]);
				delete m_pool[i].nextChunk;
				asset->~T();
			}
			delete m_freePointer;
		}

		template<typename... Args>
		T* Allocate(Args&&... args)
		{
			if (m_freePointer == nullptr) 
			{
				//Log Error, used all the free slots
				return nullptr;
			}
			Chunk<T>* chunk = m_freePointer;
			T* asset = reinterpret_cast<T*>(chunk); //check works, should only use the satrt of the chunk size to convert to asset and leave the pointer
			asset = new (asset) T(std::forward<Args>(args)...);
			m_freePointer = m_freePointer->nextChunk;
			return asset;
		}

		void Free(T* asset)
		{
			Chunk<T>* chunk = reinterpret_cast<Chunk<T>*>(asset);
			chunk->nextChunk = m_freePointer; // push to head of free list
			m_freePointer = chunk;
		}




	private:

		Chunk<T> m_pool[Capacity];
		Chunk<T>* m_freePointer;

	};



}