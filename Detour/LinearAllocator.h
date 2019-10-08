#pragma once
#include "../Unmanaged/Detour/DetourCommon.h"
#include "../Unmanaged/Detour/DetourTileCacheBuilder.h"

namespace RecastManaged
{
	namespace DetourTileCache
	{
		struct LinearAllocator : public dtTileCacheAlloc
		{
			unsigned char* buffer;
			size_t capacity;
			size_t top;
			size_t high;

			LinearAllocator(const size_t cap) : buffer(0), capacity(0), top(0), high(0)
			{
				resize(cap);
			}

			virtual ~LinearAllocator()
			{
				dtFree(buffer);
			}

			void resize(const size_t cap)
			{
				if (buffer) dtFree(buffer);
				buffer = (unsigned char*)dtAlloc(cap, DT_ALLOC_PERM);
				capacity = cap;
			}

			virtual void reset()
			{
				high = dtMax(high, top);
				top = 0;
			}

			virtual void* alloc(const size_t size)
			{
				if (!buffer)
					return 0;
				if (top + size > capacity)
					return 0;
				unsigned char* mem = &buffer[top];
				top += size;
				return mem;
			}

			virtual void free(void* /*ptr*/)
			{
				// Empty
			}
		};
	}
}
