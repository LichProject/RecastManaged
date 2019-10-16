#include "TileCacheParams.h"
#include <cstring>

RecastManaged::DetourTileCache::TileCacheParams::!TileCacheParams()
{
	if (!this->_disposed)
	{
		this->_disposed = true;
		
		delete m_TileCacheParams;
		m_TileCacheParams = nullptr;
	}
}

RecastManaged::DetourTileCache::TileCacheParams::TileCacheParams()
{
	this->m_TileCacheParams = new dtTileCacheParams;
	memset(this->m_TileCacheParams, 0, sizeof this->m_TileCacheParams);
}
