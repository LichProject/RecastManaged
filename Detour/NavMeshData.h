#pragma once
namespace RecastManaged
{
	namespace Detour
	{
		public ref class NavMeshData
		{
			bool _disposed;

		public:
			int NavDataSize;
			unsigned char* NavData;

			NavMeshData(array<unsigned char>^ navData, int startIndex, int length);

			NavMeshData(unsigned char* navData, int navDataSize);

			~NavMeshData();

			!NavMeshData();

			array<unsigned char>^ GetNavData();

			void GetNavData(array<unsigned char>^ buffer, int start);

			bool OwnsData;
		};
	}
}
