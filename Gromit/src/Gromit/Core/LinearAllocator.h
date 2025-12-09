#pragma once

namespace Gromit
{
	class LinearAllocator
	{
	public:
		uint8_t* buffer; // total area
		size_t length;
		size_t offset;
		size_t alignedOffset;

		~LinearAllocator()
		{
			delete[] buffer;
		}

		void Create(size_t size)
		{
			length = size;
			buffer = new uint8_t[length];
			offset = 0;
		}

		template<typename T>
		T* Allocate()
		{
			size_t size = sizeof(T);
			size_t align = alignof(T);

			void* ptr = AllocateBytes(size, align);
			return (T*)ptr;
		}

		void* AllocateBytes(size_t size, size_t align)
		{
			size_t mask = align - 1;
			uintptr_t currentAddress = (uintptr_t)(buffer + offset);
			uintptr_t alignedAddress = (currentAddress + mask) & ~mask;
			size_t padding = alignedAddress - currentAddress;

			if (size + offset + padding > length)
			{
				return nullptr;
			}
			offset += padding;
			void* ptr = buffer + offset;
			std::memset(ptr, 'A', size); //wrap in debug
			offset += size;
			return ptr;
		}

		void Free() 
		{
			offset = 0;
			std::memset(buffer, 'D', length);
		}
	};
}