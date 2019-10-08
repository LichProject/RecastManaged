#include "Heightfield.h"


RecastManaged::Recast::Heightfield::Heightfield()
{
	this->_hf = rcAllocHeightfield();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::Heightfield::Heightfield(rcHeightfield* hf, bool* destructWithMe)
{
	this->_hf = hf;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::Heightfield::!Heightfield()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreeHeightField(_hf);
		_hf = nullptr;
		
		this->_disposed = true;
	}
}

RecastManaged::Recast::Heightfield::~Heightfield()
{
	this->!Heightfield();
}

rcHeightfield* RecastManaged::Recast::Heightfield::GetPointer()
{
	return this->_hf;
}


#pragma region Width
void RecastManaged::Recast::Heightfield::Width::set(int value)
{
	_hf->width = value;
}

int RecastManaged::Recast::Heightfield::Width::get()
{
	return _hf->width;
}
#pragma endregion


#pragma region Height
void RecastManaged::Recast::Heightfield::Height::set(int value)
{
	_hf->height = value;
}

int RecastManaged::Recast::Heightfield::Height::get()
{
	return _hf->height;
}
#pragma endregion


#pragma region BoundsMin
void RecastManaged::Recast::Heightfield::BoundsMin::set(array<float>^ value)
{
	_hf->bmin[0] = value[0];
	_hf->bmin[1] = value[1];
	_hf->bmin[2] = value[2];
}

array<float>^ RecastManaged::Recast::Heightfield::BoundsMin::get()
{
	array<float>^ bmin =
	{
		_hf->bmin[0],
		_hf->bmin[1],
		_hf->bmin[2]
	};
	return bmin;
}
#pragma endregion


#pragma region BoundsMax
void RecastManaged::Recast::Heightfield::BoundsMax::set(array<float>^ value)
{
	_hf->bmax[0] = value[0];
	_hf->bmax[1] = value[1];
	_hf->bmax[2] = value[2];
}

array<float>^ RecastManaged::Recast::Heightfield::BoundsMax::get()
{
	array<float>^ bmax =
	{
		_hf->bmax[0],
		_hf->bmax[1],
		_hf->bmax[2]
	};
	return bmax;
}
#pragma endregion


#pragma region CellSize
void RecastManaged::Recast::Heightfield::CellSize::set(float value)
{
	_hf->cs = value;
}

float RecastManaged::Recast::Heightfield::CellSize::get()
{
	return _hf->cs;
}
#pragma endregion


#pragma region CellHeight
void RecastManaged::Recast::Heightfield::CellHeight::set(float value)
{
	_hf->ch = value;
}

float RecastManaged::Recast::Heightfield::CellHeight::get()
{
	return _hf->ch;
}
#pragma endregion
