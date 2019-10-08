#include "PolyMeshDetail.h"
#include "../Unmanaged/Recast/Recast.h"

RecastManaged::Recast::PolyMeshDetail::PolyMeshDetail()
{
	this->_mesh = rcAllocPolyMeshDetail();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::PolyMeshDetail::PolyMeshDetail(rcPolyMeshDetail* mesh, bool* destructWithMe)
{
	this->_mesh = mesh;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::PolyMeshDetail::~PolyMeshDetail()
{
	this->!PolyMeshDetail();
}

RecastManaged::Recast::PolyMeshDetail::!PolyMeshDetail()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreePolyMeshDetail(_mesh);
		_mesh = nullptr;
		
		this->_disposed = true;
	}
}

rcPolyMeshDetail* RecastManaged::Recast::PolyMeshDetail::GetPointer()
{
	return _mesh;
}

#pragma region Meshes
void RecastManaged::Recast::PolyMeshDetail::Meshes::set(unsigned* value)
{
	_mesh->meshes = value;
}

unsigned* RecastManaged::Recast::PolyMeshDetail::Meshes::get()
{
	return _mesh->meshes;
}
#pragma endregion


#pragma region Verts
void RecastManaged::Recast::PolyMeshDetail::Verts::set(float* value)
{
	_mesh->verts = value;
}

float* RecastManaged::Recast::PolyMeshDetail::Verts::get()
{
	return _mesh->verts;
}
#pragma endregion


#pragma region Tris
void RecastManaged::Recast::PolyMeshDetail::Tris::set(unsigned char* value)
{
	_mesh->tris = value;
}

unsigned char* RecastManaged::Recast::PolyMeshDetail::Tris::get()
{
	return _mesh->tris;
}
#pragma endregion


#pragma region NMeshes
void RecastManaged::Recast::PolyMeshDetail::NMeshes::set(int value)
{
	_mesh->nmeshes = value;
}

int RecastManaged::Recast::PolyMeshDetail::NMeshes::get()
{
	return _mesh->nmeshes;
}
#pragma endregion


#pragma region NVerts
void RecastManaged::Recast::PolyMeshDetail::NVerts::set(int value)
{
	_mesh->nverts = value;
}

int RecastManaged::Recast::PolyMeshDetail::NVerts::get()
{
	return _mesh->nverts;
}
#pragma endregion


#pragma region NTris
void RecastManaged::Recast::PolyMeshDetail::NTris::set(int value)
{
	_mesh->ntris = value;
}

int RecastManaged::Recast::PolyMeshDetail::NTris::get()
{
	return _mesh->ntris;
}
#pragma endregion
