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
	void* voidPtr = new dtNavMeshCreateParams();
	this->_params = static_cast<dtNavMeshCreateParams*>(voidPtr);
	memset(&voidPtr, 0, sizeof voidPtr);
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshCreateParams::NavMeshCreateParams()
{
	void* voidPtr = new dtNavMeshCreateParams();
	this->_params = static_cast<dtNavMeshCreateParams*>(voidPtr);
	memset(&voidPtr, 0, sizeof voidPtr);
	this->_destructWithMe = true;
	this->_disposed = false;
}
