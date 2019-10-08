#include "MeshHeader.h"

RecastManaged::Detour::MeshHeader::MeshHeader(dtMeshHeader* mh, bool* destructWithMe)
{
	this->_mh = mh;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}


RecastManaged::Detour::MeshHeader::MeshHeader()
{
	this->_mh = new dtMeshHeader();
	this->_destructWithMe = true;
	this->_disposed = false;
}


RecastManaged::Detour::MeshHeader::~MeshHeader()
{
	this->!MeshHeader();
}


RecastManaged::Detour::MeshHeader::!MeshHeader()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _mh;
		_mh = nullptr;
		
		this->_disposed = true;
	}
}


dtMeshHeader* RecastManaged::Detour::MeshHeader::GetPointer()
{
	return this->_mh;
}

#pragma region X
int RecastManaged::Detour::MeshHeader::X::get()
{
	return _mh->x;
}

void RecastManaged::Detour::MeshHeader::X::set(int value)
{
	_mh->x = value;
}
#pragma endregion


#pragma region Y
int RecastManaged::Detour::MeshHeader::Y::get()
{
	return _mh->y;
}

void RecastManaged::Detour::MeshHeader::Y::set(int value)
{
	_mh->y = value;
}
#pragma endregion


#pragma region Magic
int RecastManaged::Detour::MeshHeader::Magic::get()
{
	return _mh->magic;
}

void RecastManaged::Detour::MeshHeader::Magic::set(int value)
{
	_mh->magic = value;
}
#pragma endregion


#pragma region Version
int RecastManaged::Detour::MeshHeader::Version::get()
{
	return _mh->version;
}

void RecastManaged::Detour::MeshHeader::Version::set(int value)
{
	_mh->version = value;
}
#pragma endregion


#pragma region PolyCount
int RecastManaged::Detour::MeshHeader::PolyCount::get()
{
	return _mh->polyCount;
}

void RecastManaged::Detour::MeshHeader::PolyCount::set(int value)
{
	_mh->polyCount = value;
}
#pragma endregion


#pragma region VertCount
int RecastManaged::Detour::MeshHeader::VertCount::get()
{
	return _mh->vertCount;
}

void RecastManaged::Detour::MeshHeader::VertCount::set(int value)
{
	_mh->vertCount = value;
}
#pragma endregion


#pragma region MaxLinkCount
int RecastManaged::Detour::MeshHeader::MaxLinkCount::get()
{
	return _mh->maxLinkCount;
}

void RecastManaged::Detour::MeshHeader::MaxLinkCount::set(int value)
{
	_mh->maxLinkCount = value;
}
#pragma endregion


#pragma region DetailMeshCount
int RecastManaged::Detour::MeshHeader::DetailMeshCount::get()
{
	return _mh->detailMeshCount;
}

void RecastManaged::Detour::MeshHeader::DetailMeshCount::set(int value)
{
	_mh->detailMeshCount = value;
}
#pragma endregion


#pragma region DetailVertCount
int RecastManaged::Detour::MeshHeader::DetailVertCount::get()
{
	return _mh->detailVertCount;
}

void RecastManaged::Detour::MeshHeader::DetailVertCount::set(int value)
{
	_mh->detailVertCount = value;
}
#pragma endregion


#pragma region DetailTriCount
int RecastManaged::Detour::MeshHeader::DetailTriCount::get()
{
	return _mh->detailTriCount;
}

void RecastManaged::Detour::MeshHeader::DetailTriCount::set(int value)
{
	_mh->detailTriCount = value;
}
#pragma endregion


#pragma region BVNodeCount
int RecastManaged::Detour::MeshHeader::BVNodeCount::get()
{
	return _mh->bvNodeCount;
}

void RecastManaged::Detour::MeshHeader::BVNodeCount::set(int value)
{
	_mh->bvNodeCount = value;
}
#pragma endregion


#pragma region OffMeshConCount
int RecastManaged::Detour::MeshHeader::OffMeshConCount::get()
{
	return _mh->offMeshConCount;
}

void RecastManaged::Detour::MeshHeader::OffMeshConCount::set(int value)
{
	_mh->offMeshConCount = value;
}
#pragma endregion


#pragma region OffMeshBase
int RecastManaged::Detour::MeshHeader::OffMeshBase::get()
{
	return _mh->offMeshBase;
}

void RecastManaged::Detour::MeshHeader::OffMeshBase::set(int value)
{
	_mh->offMeshBase = value;
}
#pragma endregion


#pragma region WalkableHeight
float RecastManaged::Detour::MeshHeader::WalkableHeight::get()
{
	return _mh->walkableHeight;
}

void RecastManaged::Detour::MeshHeader::WalkableHeight::set(float value)
{
	_mh->walkableHeight = value;
}
#pragma endregion


#pragma region WalkableRadius
float RecastManaged::Detour::MeshHeader::WalkableRadius::get()
{
	return _mh->walkableRadius;
}

void RecastManaged::Detour::MeshHeader::WalkableRadius::set(float value)
{
	_mh->walkableRadius = value;
}
#pragma endregion


#pragma region WalkableClimb
float RecastManaged::Detour::MeshHeader::WalkableClimb::get()
{
	return _mh->walkableClimb;
}

void RecastManaged::Detour::MeshHeader::WalkableClimb::set(float value)
{
	_mh->walkableClimb = value;
}
#pragma endregion


#pragma region BVQuantFactor
float RecastManaged::Detour::MeshHeader::BVQuantFactor::get()
{
	return _mh->bvQuantFactor;
}

void RecastManaged::Detour::MeshHeader::BVQuantFactor::set(float value)
{
	_mh->bvQuantFactor = value;
}
#pragma endregion
