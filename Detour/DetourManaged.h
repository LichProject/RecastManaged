#pragma once
#include "NavMeshData.h"
#include "../Recast/HeightfieldLayerSet.h"
#include "NavMeshCreateParams.h"

using namespace System::Runtime::InteropServices;

namespace RecastManaged
{
	namespace Detour
	{
		public ref class Detour
		{
		public:
			static bool CreateNavMeshData(NavMeshCreateParams^ navMeshCreateParams, [Out] NavMeshData^% data);

			static System::Collections::Generic::List<NavMeshData^>^
			BuildTileCacheLayers(Recast::HeightfieldLayerSet^ layerSet, int x, int y);
		};
	}
}
