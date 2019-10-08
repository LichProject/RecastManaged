#include "TileCache.h"
#include "../Unmanaged/Detour/DetourCommon.h"

RecastManaged::DetourTileCache::TileCache::TileCache(TileCacheParams^ tileCacheParams)
{
	m_talloc = new LinearAllocator(32000);
	m_tcomp = new DummyCompressor;
	m_tmproc = new MeshProcess;

	this->m_Parameters = tileCacheParams;
	this->m_TileCache = dtAllocTileCache();

	if (!this->m_TileCache)
	{
		throw gcnew Exception("Could not allocate tile cache ['dtAllocTileCache' failed].");
	}

	const auto status = this->m_TileCache->init(m_Parameters->GetPointer(), m_talloc, m_tcomp, m_tmproc);

	if (dtStatusFailed(status))
	{
		throw gcnew Exception("Could not init tile cache - FAILED.");
	}

	if ((status & unsigned(Detour::StatusDetailFlag::OutOfMemory)) != 0)
	{
		throw gcnew Exception("Could not init tile cache - DT_OUT_OF_MEMORY.");
	}

	if ((status & unsigned(Detour::StatusDetailFlag::InvalidParam)) != 0)
	{
		throw gcnew Exception("Could not init tile cache - DT_INVALID_PARAM.");
	}

	if (!dtStatusSucceed(status))
	{
		throw gcnew Exception("Could not init tile cache - " + status);
	}
}

RecastManaged::DetourTileCache::TileCache::!TileCache()
{
	if (!this->_disposed)
	{
		this->_disposed = true;

		dtFreeTileCache(m_TileCache);
		m_TileCache = nullptr;

		delete m_Parameters;
		m_Parameters = nullptr;

		delete m_tmproc;
		m_tmproc = nullptr;

		delete m_tcomp;
		m_tcomp = nullptr;

		delete m_talloc;
		m_talloc = nullptr;
	}
}

bool RecastManaged::DetourTileCache::TileCache::AddTile(Detour::NavMeshData^ data, unsigned% tileRef)
{
	unsigned result;

	const unsigned status = this->m_TileCache->addTile(data->NavData, data->NavDataSize, DT_COMPRESSEDTILE_FREE_DATA,
	                                                   &result);
	//if ((status & DT_WRONG_MAGIC) != 0)
	//{
	//	data->OwnsData = false;
	//}

	if (dtStatusFailed(status))
	{
		data->OwnsData = false;
		
		dtFree(data->NavData);
		data->NavData = 0;
	}

	tileRef = result;
	return true;
}

bool RecastManaged::DetourTileCache::TileCache::RemoveTile(unsigned tileRef)
{
	auto const status = this->m_TileCache->removeTile(tileRef, nullptr, nullptr);
	return (status & DT_SUCCESS) != 0;
}

unsigned RecastManaged::DetourTileCache::TileCache::GetTileAt(int x, int y, int layer)
{
	const auto tile = this->m_TileCache->getTileAt(x, y, layer);
	if (tile != nullptr)
	{
		return this->m_TileCache->getTileRef(tile);
	}

	return 0u;
}

bool RecastManaged::DetourTileCache::TileCache::BuildTilesAt(int x, int y, Detour::NavMesh^ mesh)
{
	return (this->m_TileCache->buildNavMeshTilesAt(x, y, mesh->GetPointer()) & DT_SUCCESS) != 0;
}

bool RecastManaged::DetourTileCache::TileCache::BuildTile(unsigned tile, Detour::NavMesh^ mesh)
{
	return (this->m_TileCache->buildNavMeshTile(tile, mesh->GetPointer()) & DT_SUCCESS) != 0;
}

bool RecastManaged::DetourTileCache::TileCache::BuildTile(Detour::TileReference^ tile, Detour::NavMesh^ mesh)
{
	return (this->m_TileCache->buildNavMeshTile(tile->Id, mesh->GetPointer()) & DT_SUCCESS) != 0;
}

RecastManaged::Detour::StatusDetailFlag RecastManaged::DetourTileCache::TileCache::AddTempBoxObstacle(
	Tools::Math::Vector3^ bmin, Tools::Math::Vector3^ bmax, unsigned% obstacleRef)
{
	if (this->m_TileCache == nullptr)
	{
		return Detour::StatusDetailFlag::Failure;
	}

	bmin->Y = -50;
	bmax->Y = 50;

	pin_ptr<float> pinBMin = &bmin->X;
	pin_ptr<float> pinBMax = &bmax->X;

	unsigned result;

	const auto status = this->m_TileCache->addBoxObstacle(pinBMin, pinBMax, &result);
	obstacleRef = result;

	return Detour::StatusDetailFlag(status);
}

RecastManaged::Detour::StatusDetailFlag RecastManaged::DetourTileCache::TileCache::AddTempObstacle(
	Tools::Math::Vector3^ pos, float radius, unsigned% obstacleRef)
{
	if (this->m_TileCache == nullptr)
	{
		return Detour::StatusDetailFlag::Failure;
	}

	pos->Y = -500;

	pin_ptr<float> pinPos = &pos->X;
	unsigned result;

	auto const status = this->m_TileCache->addObstacle(pinPos, radius, 1000, &result);
	obstacleRef = result;

	return Detour::StatusDetailFlag(status);
}

void RecastManaged::DetourTileCache::TileCache::RemoveTempObstacle(Tools::Math::Vector3^ pos)
{
	pos->Y = -500;

	pin_ptr<float> pinPos = &pos->X;

	for (int i = 0; i < this->m_Parameters->MaxObstacles; ++i)
	{
		auto const obstacle = this->m_TileCache->getObstacle(i);

		if (dtVdistSqr(pinPos, obstacle->cylinder.pos) < 4)
		{
			this->m_TileCache->removeObstacle(this->m_TileCache->getObstacleRef(obstacle));
		}
	}
}

bool RecastManaged::DetourTileCache::TileCache::RemoveTempObstacle(unsigned obstacleRef)
{
	if (this->m_TileCache == nullptr)
	{
		return false;
	}

	return (this->m_TileCache->removeObstacle(obstacleRef) & DT_SUCCESS) != 0;
}

void RecastManaged::DetourTileCache::TileCache::ClearAllTempObstacles()
{
	if (this->m_TileCache == nullptr)
	{
		return;
	}

	for (int i = 0; i < this->m_TileCache->getObstacleCount(); ++i)
	{
		const dtTileCacheObstacle* ob = this->m_TileCache->getObstacle(i);
		if (ob->state == DT_OBSTACLE_EMPTY)
			continue;

		this->m_TileCache->removeObstacle(this->m_TileCache->getObstacleRef(ob));
	}
}

RecastManaged::Detour::StatusDetailFlag RecastManaged::DetourTileCache::TileCache::Update(Detour::NavMesh^ mesh,
                                                                                          bool% upToDate)
{
	bool result;

	const auto status = this->m_TileCache->update(0, mesh->GetPointer(), &result);
	upToDate = result;

	return Detour::StatusDetailFlag(status);
}

static const int TILECACHESET_MAGIC = 'T' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'TSET';
static const int TILECACHESET_VERSION = 1;

struct TileCacheSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams meshParams;
	dtTileCacheParams cacheParams;
};

struct TileCacheTileHeader
{
	dtCompressedTileRef tileRef;
	int dataSize;
};

bool RecastManaged::DetourTileCache::TileCache::SaveAll(String^ mPath, Detour::NavMesh^ navMesh)
{
	const auto m_navmesh = navMesh->GetPointer();
	const auto m_tileCache = this->GetPointer();

	if (!m_tileCache)
	{
		return false;
	}

	if (!m_navmesh)
	{
		return false;
	}

	auto path = (char*)(void*)Marshal::StringToHGlobalAnsi(mPath);

	FILE* fp = fopen(path, "wb");
	Marshal::FreeHGlobal((IntPtr)path);

	if (!fp)
	{
		return false;
	}

	// Store header.
	TileCacheSetHeader header;
	header.magic = TILECACHESET_MAGIC;
	header.version = TILECACHESET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < m_tileCache->getTileCount(); ++i)
	{
		const dtCompressedTile* tile = m_tileCache->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.cacheParams, m_tileCache->getParams(), sizeof(dtTileCacheParams));
	memcpy(&header.meshParams, m_navmesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(TileCacheSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < m_tileCache->getTileCount(); ++i)
	{
		const dtCompressedTile* tile = m_tileCache->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		TileCacheTileHeader tileHeader;
		tileHeader.tileRef = m_tileCache->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);

		fwrite(tile->data, tile->dataSize, 1, fp);
	}

	fclose(fp);
	return true;
}
