#pragma once
#include "Status.h"
#include "../Unmanaged/Detour/DetourNavMeshQuery.h"
#include "../Tools/Math/Vector3.h"
#include "NavMesh.h"
#include "StraightPathFlags.h"
#include "QueryFilter.h"
#include "LoadTileDelegate.h"

using namespace Runtime::InteropServices;

namespace RecastManaged
{
	namespace Detour
	{
		public ref class NavMeshQuery
		{
			dtNavMeshQuery* _query;
			bool _destructWithMe;
			bool _disposed;
			LoadTileDelegate^ _tileLoaderDel;

		public:
			NavMeshQuery(dtNavMeshQuery* query, bool* destructWithMe);

			NavMeshQuery();

			~NavMeshQuery()
			{
				this->!NavMeshQuery();
			}

			!NavMeshQuery();

			Status^ Init(NavMesh^ mesh, int maxNodes);

			Status^ FindNearestPolygon(Tools::Math::Vector3^ center, Tools::Math::Vector3^ extents, QueryFilter^ filter,
			                           [Out] Tools::Math::Vector3^% nearestPt,
			                           [Out] PolygonReference^% result);

			Status^ QueryPolygons(Tools::Math::Vector3^ center, Tools::Math::Vector3^ extents, QueryFilter^ filter,
			                      int maxPolys, [Out] array<PolygonReference^>^% result);

			Status^ FindPath(PolygonReference^ startRef, PolygonReference^ endRef, Tools::Math::Vector3^ startPos,
			                 Tools::Math::Vector3^ endPos, QueryFilter^ filter, int maxPathSize,
			                 [Out] array<PolygonReference^>^% result);

			Status^ FindStraightPath(Tools::Math::Vector3^ startPos, Tools::Math::Vector3^ endPos,
			                         array<PolygonReference^>^ polyPath,
			                         int maxStraightPathSize,
			                         [Out] array<Tools::Math::Vector3^>^% points,
			                         [Out] array<StraightPathFlags>^% straightPathFlags,
			                         [Out] array<PolygonReference^>^% straightPathRef);

			Status^ Raycast(PolygonReference^ startRef, Tools::Math::Vector3^ startPos, Tools::Math::Vector3^ endPos,
			                QueryFilter^ filter, int maxPolys,
			                [Out] array<PolygonReference^>^% result,
			                [Out] float% t,
			                [Out] Tools::Math::Vector3^% hitNormal);

			Status^ FindDistanceToWall(PolygonReference^ centerRef, Tools::Math::Vector3^ centerPos, float maxRadius,
			                           QueryFilter^ filter,
			                           [Out] float% result,
			                           [Out] Tools::Math::Vector3^% hitPos,
			                           [Out] Tools::Math::Vector3^% hitNormal);

			Status^ FindRandomPointAroundCircle(PolygonReference^ startRef, Tools::Math::Vector3^ centerPos,
			                                    float maxRadius, QueryFilter^ filter,
			                                    [Out] PolygonReference^% randomRef,
			                                    [Out] Tools::Math::Vector3^% randomPoint);

			void SetTileLoaderFunction(LoadTileDelegate^ del);
		};
	}
}
