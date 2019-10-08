#pragma once
#include "../Unmanaged/Recast/Recast.h"
#include "Heightfield.h"
#include "CompactHeightfield.h"
#include "HeightfieldLayerSet.h"
#include "PolyMesh.h"

using namespace System::Runtime::InteropServices;

namespace RecastManaged
{
	namespace Recast
	{
		public ref class Recast
		{
			static rcContext* _context;

		public:
			static Recast()
			{
				_context = new rcContext();
			}

			static bool BuildCompactHeightfield(int walkableHeight, int walkableClimb, Heightfield^ hf,
			                                    [Out] CompactHeightfield^% chf);

			static bool BuildHeightfieldLayers(int walkableHeight, int borderSize, CompactHeightfield^ chf,
			                                   [Out] HeightfieldLayerSet^% lset);

			static bool CreateHeightfield(int width, int height, array<float>^ bmin, array<float>^ bmax, float cs,
			                              float ch, [Out] Heightfield^% hf);

			static bool CreateHeightfield(int width, int height, Tools::Math::Vector3^ bmin, Tools::Math::Vector3^ bmax,
			                              float cs, float ch, [Out] Heightfield^% hf);

			static bool ErodeWalkableArea(int radius, CompactHeightfield^ chf);

			static void FilterLedgeSpans(int walkableHeight, int walkableClimb, Heightfield^ solid);

			static void FilterLowHangingWalkableObstacles(int walkableClimb, Heightfield^ solid);

			static void FilterWalkableLowHeightSpans(int walkableHeight, Heightfield^ solid);

			static void MarkConvexPolyArea(array<float>^ verts, int nverts, float heightMin, float heightMax, int area,
			                               CompactHeightfield^ chf);

			static bool RasterizeTriangles(array<float>^ verts, int* tris, int ntris, array<unsigned char>^ areas,
			                               Heightfield^ solid, int flagMergeThr);

			static void MarkWalkableTriangles(const float walkableSlopeAngle, const array<float>^ verts, int nv,
			                                  int* tris, int nt, array<unsigned char>^% areas);
		};
	}
}
