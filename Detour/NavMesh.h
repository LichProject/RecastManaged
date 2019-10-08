#pragma once
#include "NavMeshData.h"
#include "Status.h"
#include "PolygonReference.h"
#include "NavMeshParams.h"
#include "TileReference.h"
#include "MeshTile.h"

using namespace System;
using namespace Runtime::InteropServices;

namespace RecastManaged
{
	namespace Detour
	{
		public ref class NavMesh
		{
			dtNavMesh* _mesh;
			bool _destructWithMe;
			bool _disposed;

		public:
			NavMesh(dtNavMesh* mesh, bool destructWithMe);
			NavMesh();

			!NavMesh();
			~NavMesh();

			dtNavMesh* GetPointer();

			Status^ Init(NavMeshData^ data);

			Status^ Init(NavMeshParams^ params);

			Status^ AddTile(NavMeshData^ data, [Out] TileReference^% tileRef);

			Status^ RemoveTile(TileReference^ tileRef);

			Status^ RemoveTile(TileReference^ tileRef, [Out] NavMeshData^% data);

			MeshTile^ GetTileAt(int x, int y, int layer);

			TileReference^ GetTileRefAt(int x, int y, int layer);

			TileReference^ GetTileRef(MeshTile^ tile);

			int GetMaxTiles();

			MeshTile^ GetTile(int i);

			int GetTileStateSize(MeshTile^ tile);

			Status^ RestoreTileState(MeshTile^ tile, array<unsigned char>^ data);

			void SetPolyFlags(PolygonReference^ polyRef, unsigned short flags);

			Status^ GetPolyFlags(PolygonReference^ polyRef, [Out] unsigned short^% flags);

			void SetPolyArea(PolygonReference^ polyRef, unsigned char area);

			Status^ GetPolyArea(PolygonReference^ polyRef, [Out] unsigned char^% area);

			PolygonReference^ EncodePolyId(unsigned salt, unsigned it, unsigned ip);

			void DecodePolyId(PolygonReference^ polyRef, [Out] unsigned^% salt, [Out] unsigned^% it,
			                  [Out] unsigned^% ip);

			unsigned DecodePolyIdSalt(PolygonReference^ polyRef);

			unsigned DecodePolyIdTile(PolygonReference^ polyRef);

			unsigned DecodePolyIdPoly(PolygonReference^ polyRef);

			Collections::Generic::List<MeshTile^>^ GetAllTiles();

			static NavMesh^ LoadAll(String^ path);
		};
	}
}
