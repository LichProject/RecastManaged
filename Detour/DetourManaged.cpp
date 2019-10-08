#include "DetourManaged.h"
#include "../Unmanaged/Detour/DetourNavMeshBuilder.h"
#include "../Unmanaged/Detour/DetourTileCacheBuilder.h"
#include "../Unmanaged/Detour/DetourCommon.h"
#include "DummyCompressor.h"
#include "../Recast/CompactHeightfield.h"

bool RecastManaged::Detour::Detour::CreateNavMeshData(NavMeshCreateParams^ navMeshCreateParams, NavMeshData^% data)
{
	unsigned char* navData = nullptr;
	int navDataSize = 0;
	const bool result = dtCreateNavMeshData(navMeshCreateParams->GetPointer(), &navData, &navDataSize);
	data = gcnew NavMeshData(navData, navDataSize);
	return result;
}

System::Collections::Generic::List<RecastManaged::Detour::NavMeshData^>^ RecastManaged::Detour::Detour::
BuildTileCacheLayers(Recast::HeightfieldLayerSet^ layerSet, int x, int y)
{
	auto list = gcnew System::Collections::Generic::List<NavMeshData^>();
	auto const lset = layerSet->GetPointer();

	DetourTileCache::DummyCompressor comp;
	
	for (int i = 0; i < rcMin(lset->nlayers, 32); ++i)
	{
		unsigned char* navData = nullptr;
		int navDataSize = 0;

		const rcHeightfieldLayer* layer = &lset->layers[i];

		// Store header
		dtTileCacheLayerHeader header;
		header.magic = DT_TILECACHE_MAGIC;
		header.version = DT_TILECACHE_VERSION;

		// Tile layer location in the navmesh.
		header.tx = x;
		header.ty = y;
		header.tlayer = i;
		dtVcopy(header.bmin, layer->bmin);
		dtVcopy(header.bmax, layer->bmax);

		// Tile info.
		header.width = (unsigned char)layer->width;
		header.height = (unsigned char)layer->height;
		header.minx = (unsigned char)layer->minx;
		header.maxx = (unsigned char)layer->maxx;
		header.miny = (unsigned char)layer->miny;
		header.maxy = (unsigned char)layer->maxy;
		header.hmin = (unsigned short)layer->hmin;
		header.hmax = (unsigned short)layer->hmax;

		dtStatus status = dtBuildTileCacheLayer(&comp, &header, layer->heights, layer->areas, layer->cons, &navData, &navDataSize);
		if (dtStatusFailed(status))
		{
			continue;
		}
		
		list->Add(gcnew NavMeshData(navData, navDataSize));
	}

	return list;
}
