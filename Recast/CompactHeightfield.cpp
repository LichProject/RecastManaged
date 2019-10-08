#include "../Unmanaged/Recast/Recast.h"
#include "../Tools/Math/Vector3.h"
#include "CompactHeightfield.h"

RecastManaged::Recast::CompactHeightfield::CompactHeightfield()
{
	this->_chf = rcAllocCompactHeightfield();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::CompactHeightfield::CompactHeightfield(rcCompactHeightfield* chf, bool* destructWithMe)
{
	this->_chf = chf;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::CompactHeightfield::~CompactHeightfield()
{
	this->!CompactHeightfield();
}

RecastManaged::Recast::CompactHeightfield::!CompactHeightfield()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreeCompactHeightfield(_chf);
		_chf = nullptr;
		
		this->_disposed = true;
	}
}

rcCompactHeightfield* RecastManaged::Recast::CompactHeightfield::GetPointer()
{
	return _chf;
}

#pragma region Areas
unsigned char* RecastManaged::Recast::CompactHeightfield::Areas::get()
{
	return _chf->areas;
}

void RecastManaged::Recast::CompactHeightfield::Areas::set(unsigned char* value)
{
	_chf->areas = value;
}
#pragma endregion


#pragma region BMax
RecastManaged::Tools::Math::Vector3^ RecastManaged::Recast::CompactHeightfield::BMax::get()
{
	const auto bmax = _chf->bmax;
	return gcnew Tools::Math::Vector3(bmax[0], bmax[1], bmax[2]);
}

void RecastManaged::Recast::CompactHeightfield::BMax::set(Tools::Math::Vector3^ value)
{
	_chf->bmax[0] = value->X;
	_chf->bmax[1] = value->Y;
	_chf->bmax[2] = value->Z;
}
#pragma endregion


#pragma region BMin
RecastManaged::Tools::Math::Vector3^ RecastManaged::Recast::CompactHeightfield::BMin::get()
{
	const auto bmin = _chf->bmin;
	return gcnew Tools::Math::Vector3(bmin[0], bmin[1], bmin[2]);
}

void RecastManaged::Recast::CompactHeightfield::BMin::set(Tools::Math::Vector3^ value)
{
	_chf->bmin[0] = value->X;
	_chf->bmin[1] = value->Y;
	_chf->bmin[2] = value->Z;
}
#pragma endregion


#pragma region CellHeight
float RecastManaged::Recast::CompactHeightfield::CellHeight::get()
{
	return _chf->ch;
}

void RecastManaged::Recast::CompactHeightfield::CellHeight::set(float value)
{
	_chf->ch = value;
}
#pragma endregion


#pragma region CellSize
float RecastManaged::Recast::CompactHeightfield::CellSize::get()
{
	return _chf->cs;
}

void RecastManaged::Recast::CompactHeightfield::CellSize::set(float value)
{
	_chf->cs = value;
}
#pragma endregion


#pragma region Height
int RecastManaged::Recast::CompactHeightfield::Height::get()
{
	return _chf->height;
}

void RecastManaged::Recast::CompactHeightfield::Height::set(int value)
{
	_chf->height = value;
}
#pragma endregion


#pragma region WalkableClimb
int RecastManaged::Recast::CompactHeightfield::WalkableClimb::get()
{
	return _chf->walkableClimb;
}

void RecastManaged::Recast::CompactHeightfield::WalkableClimb::set(int value)
{
	_chf->walkableClimb = value;
}
#pragma endregion


#pragma region WalkableHeight
int RecastManaged::Recast::CompactHeightfield::WalkableHeight::get()
{
	return _chf->walkableHeight;
}

void RecastManaged::Recast::CompactHeightfield::WalkableHeight::set(int value)
{
	_chf->walkableHeight = value;
}
#pragma endregion


#pragma region Width
int RecastManaged::Recast::CompactHeightfield::Width::get()
{
	return _chf->width;
}

void RecastManaged::Recast::CompactHeightfield::Width::set(int value)
{
	_chf->width = value;
}
#pragma endregion
