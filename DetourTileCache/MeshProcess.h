#pragma once
#include "../Unmanaged/InputGeom.h"
#include "../Unmanaged/Detour/DetourTileCache.h"
#include "../Unmanaged/Detour/DetourTileCacheBuilder.h"
#include "../Unmanaged/Detour/DetourNavMeshBuilder.h"

namespace RecastManaged
{
	namespace DetourTileCache
	{
		enum SamplePolyAreas
		{
			SAMPLE_POLYAREA_GROUND,
			SAMPLE_POLYAREA_WATER,
			SAMPLE_POLYAREA_ROAD,
			SAMPLE_POLYAREA_DOOR,
			SAMPLE_POLYAREA_GRASS,
			SAMPLE_POLYAREA_JUMP,
		};

		enum SamplePolyFlags
		{
			SAMPLE_POLYFLAGS_WALK = 0x01,
			// Ability to walk (ground, grass, road)
			SAMPLE_POLYFLAGS_SWIM = 0x02,
			// Ability to swim (water).
			SAMPLE_POLYFLAGS_DOOR = 0x04,
			// Ability to move through doors.
			SAMPLE_POLYFLAGS_JUMP = 0x08,
			// Ability to jump.
			SAMPLE_POLYFLAGS_DISABLED = 0x10,
			// Disabled polygon
			SAMPLE_POLYFLAGS_ALL = 0xffff // All abilities.
		};

		struct MeshProcess : public dtTileCacheMeshProcess
		{
			InputGeom* m_geom;

			inline MeshProcess() : m_geom(0)
			{
			}

			inline void init(InputGeom* geom)
			{
				m_geom = geom;
			}

			virtual void process(dtNavMeshCreateParams* params,
			                     unsigned char* polyAreas, unsigned short* polyFlags)
			{
				// Update poly flags from areas.
				for (int i = 0; i < params->polyCount; ++i)
				{
					if (polyAreas[i] == DT_TILECACHE_WALKABLE_AREA)
						polyAreas[i] = SAMPLE_POLYAREA_GROUND;

					if (polyAreas[i] == SAMPLE_POLYAREA_GROUND ||
						polyAreas[i] == SAMPLE_POLYAREA_GRASS ||
						polyAreas[i] == SAMPLE_POLYAREA_ROAD)
					{
						polyFlags[i] = SAMPLE_POLYFLAGS_WALK;
					}
					else if (polyAreas[i] == SAMPLE_POLYAREA_WATER)
					{
						polyFlags[i] = SAMPLE_POLYFLAGS_SWIM;
					}
					else if (polyAreas[i] == SAMPLE_POLYAREA_DOOR)
					{
						polyFlags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
					}
				}

				// Pass in off-mesh connections.
				if (m_geom)
				{
					params->offMeshConVerts = m_geom->getOffMeshConnectionVerts();
					params->offMeshConRad = m_geom->getOffMeshConnectionRads();
					params->offMeshConDir = m_geom->getOffMeshConnectionDirs();
					params->offMeshConAreas = m_geom->getOffMeshConnectionAreas();
					params->offMeshConFlags = m_geom->getOffMeshConnectionFlags();
					params->offMeshConUserID = m_geom->getOffMeshConnectionId();
					params->offMeshConCount = m_geom->getOffMeshConnectionCount();
				}
			}
		};
	}
}
