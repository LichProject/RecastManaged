#pragma once
#include "TileCacheParams.h"
#include "../Detour/StatusDetailFlag.h"
#include "../Detour/NavMesh.h"
#include "../Detour/DummyCompressor.h"
#include "../Detour/LinearAllocator.h"
#include "MeshProcess.h"

using namespace Runtime::InteropServices;

namespace RecastManaged
{
	namespace DetourTileCache
	{
		public ref class TileCache
		{
			bool _disposed = false;
			TileCacheParams^ m_Parameters;
			dtTileCache* m_TileCache;
			DummyCompressor* m_tcomp;
			LinearAllocator* m_talloc;
			MeshProcess* m_tmproc;

		public:
			TileCache(TileCacheParams^ tileCacheParams);

			~TileCache()
			{
				this->!TileCache();
			}

			!TileCache();

			dtTileCache* GetPointer()
			{
				return m_TileCache;
			}

			bool AddTile(Detour::NavMeshData^ data, [Out] unsigned% tileRef);

			bool RemoveTile(unsigned tileRef);

			unsigned GetTileAt(int x, int y, int layer);

			bool BuildTilesAt(int x, int y, Detour::NavMesh^ mesh);

			bool BuildTile(unsigned tile, Detour::NavMesh^ mesh);

			bool BuildTile(Detour::TileReference^ tile, Detour::NavMesh^ mesh);

			Detour::StatusDetailFlag AddTempBoxObstacle(Tools::Math::Vector3^ bmin, Tools::Math::Vector3^ bmax,
			                                            [Out] unsigned% obstacleRef);

			Detour::StatusDetailFlag
			AddTempObstacle(Tools::Math::Vector3^ pos, float radius, [Out] unsigned% obstacleRef);

			void RemoveTempObstacle(Tools::Math::Vector3^ pos);

			bool RemoveTempObstacle(unsigned obstacleRef);

			void ClearAllTempObstacles();

			Detour::StatusDetailFlag Update(Detour::NavMesh^ mesh, [Out] bool% upToDate);

			bool SaveAll(String^ mPath, Detour::NavMesh^ navMesh);
		};
	}
}
