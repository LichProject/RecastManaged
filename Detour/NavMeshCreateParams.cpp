#include "NavMeshCreateParams.h"
#include <cstring>

RecastManaged::Detour::NavMeshCreateParams::NavMeshCreateParams(dtNavMeshCreateParams* navMeshCreateParams,
                                                                bool* destructWithMe)
{
	this->_params = navMeshCreateParams;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshCreateParams::NavMeshCreateParams(bool* destructWithMe)
{
	this->_params = new dtNavMeshCreateParams;
	memset(this->_params, 0, sizeof this->_params);
	
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshCreateParams::NavMeshCreateParams()
{
	this->_params = new dtNavMeshCreateParams;
	memset(this->_params, 0, sizeof this->_params);
	
	this->_destructWithMe = true;
	this->_disposed = false;
}
