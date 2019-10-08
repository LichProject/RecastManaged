#include "NavMeshParams.h"

RecastManaged::Detour::NavMeshParams::NavMeshParams(dtNavMeshParams* nmp, bool* destructWithMe)
{
	this->_nmp = nmp;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshParams::NavMeshParams(bool* destructWithMe)
{
	this->_nmp = new dtNavMeshParams();
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshParams::NavMeshParams()
{
	this->_nmp = new dtNavMeshParams();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshParams::~NavMeshParams()
{
	this->!NavMeshParams();
}

RecastManaged::Detour::NavMeshParams::!NavMeshParams()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _nmp;
		_nmp = nullptr;
		
		this->_disposed = true;
	}
}

dtNavMeshParams* RecastManaged::Detour::NavMeshParams::GetPointer()
{
	return this->_nmp;
}

#pragma region Origin
void RecastManaged::Detour::NavMeshParams::Origin::set(Tools::Math::Vector3^ value)
{
	_nmp->orig[0] = value->X;
	_nmp->orig[1] = value->Y;
	_nmp->orig[2] = value->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Detour::NavMeshParams::Origin::get()
{
	auto const orig = _nmp->orig;
	return gcnew RecastManaged::Tools::Math::Vector3(orig[0], orig[1], orig[2]);
}
#pragma endregion


#pragma region TileHeight
void RecastManaged::Detour::NavMeshParams::TileHeight::set(float value)
{
	_nmp->tileHeight = value;
}

float RecastManaged::Detour::NavMeshParams::TileHeight::get()
{
	return _nmp->tileHeight;
}
#pragma endregion


#pragma region TileWidth
void RecastManaged::Detour::NavMeshParams::TileWidth::set(float value)
{
	_nmp->tileWidth = value;
}

float RecastManaged::Detour::NavMeshParams::TileWidth::get()
{
	return _nmp->tileWidth;
}
#pragma endregion


#pragma region MaxPolys
void RecastManaged::Detour::NavMeshParams::MaxPolys::set(int value)
{
	_nmp->maxPolys = value;
}

int RecastManaged::Detour::NavMeshParams::MaxPolys::get()
{
	return _nmp->maxPolys;
}
#pragma endregion


#pragma region MaxTiles
void RecastManaged::Detour::NavMeshParams::MaxTiles::set(int value)
{
	_nmp->maxTiles = value;
}

int RecastManaged::Detour::NavMeshParams::MaxTiles::get()
{
	return _nmp->maxTiles;
}
#pragma endregion
