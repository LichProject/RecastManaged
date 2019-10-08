#pragma once
#include "../Unmanaged/Detour/DetourTileCacheBuilder.h"
#include "../Unmanaged/fastlz.h"

namespace RecastManaged
{
	namespace DetourTileCache
	{
		class DummyCompressor : public dtTileCacheCompressor
		{
			int maxCompressedSize(const int bufferSize) override
			{
				return (int)(bufferSize * 1.05f);
			}

			dtStatus compress(const unsigned char* buffer, const int bufferSize,
			                  unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize) override
			{
				*compressedSize = fastlz_compress((const void* const)buffer, bufferSize, compressed);
				return DT_SUCCESS;
			}

			dtStatus decompress(const unsigned char* compressed, const int compressedSize,
			                    unsigned char* buffer, const int maxBufferSize, int* bufferSize) override
			{
				*bufferSize = fastlz_decompress(compressed, compressedSize, buffer, maxBufferSize);
				return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
			}
		};
	}
}
