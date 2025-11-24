#pragma once

#include "Logging/Logging.h"
#include <iostream>
#include <typeinfo>
#include <iomanip> // for setw

namespace Gromit
{
    template<typename T>
    struct Chunk
    {
        alignas(T) unsigned char asset[sizeof(T)];
        Chunk* nextChunk;
        bool inUse = false; // track usage for debug
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
            std::cout << "Pool Created for Type: " << typeid(T).name()
                << ", Capacity: " << Capacity
                << ", Element Size: " << sizeof(T) << "\n";
        }

        ~PoolAllocator()
        {
            // Destroy all constructed objects
            for (size_t i = 0; i < Capacity; i++)
            {
                if (m_pool[i].inUse)
                {
                    T* asset = reinterpret_cast<T*>(&m_pool[i]);
                    asset->~T();
                    m_pool[i].inUse = false;
                }
            }
            std::cout << "Pool Deleted for Type: " << typeid(T).name()
                << ", Capacity: " << Capacity
                << ", Element Size: " << sizeof(T) << "\n";
           // DebugPrint();
        }

        template<typename... Args>
        T* Allocate(Args&&... args)
        {
            if (m_freePointer == nullptr)
            {
                std::cerr << "[PoolAllocator] Error: pool exhausted for type " << typeid(T).name() << "\n";
                return nullptr;
            }

            Chunk<T>* chunk = m_freePointer;
            T* asset = reinterpret_cast<T*>(chunk);
            asset = new (asset) T(std::forward<Args>(args)...);
            m_freePointer = m_freePointer->nextChunk;
            chunk->inUse = true;
            //DebugPrint();
            return asset;
        }

        void Free(T* asset)
        {
            if (!asset) return;

            asset->~T(); // destroy object

            Chunk<T>* chunk = reinterpret_cast<Chunk<T>*>(asset);
            chunk->nextChunk = m_freePointer; // push to free list
            m_freePointer = chunk;
            chunk->inUse = false;
           // DebugPrint();
        }

        void DebugPrint() const
        {
            size_t used = 0;
            for (size_t i = 0; i < Capacity; i++)
                if (m_pool[i].inUse) used++;

            std::cout << "\n[PoolAllocator Debug] Type: " << typeid(T).name() << "\n";
            std::cout << "Capacity: " << Capacity << ", Element Size: " << sizeof(T)
                << ", Used: " << used << ", Free: " << (Capacity - used) << "\n";

            // simple bar graph
            std::cout << "[";
            for (size_t i = 0; i < Capacity; i++)
            {
                if (m_pool[i].inUse)
                    std::cout << "#";
                else
                    std::cout << "-";
            }
            std::cout << "]\n\n";
        }

    private:
        Chunk<T> m_pool[Capacity];
        Chunk<T>* m_freePointer;
    };
}
