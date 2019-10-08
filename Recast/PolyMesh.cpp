#include "PolyMesh.h"

RecastManaged::Recast::PolyMesh::PolyMesh()
{
	this->_mesh = rcAllocPolyMesh();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::PolyMesh::PolyMesh(rcPolyMesh* mesh, bool* destructWithMe)
{
	this->_mesh = mesh;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::PolyMesh::!PolyMesh()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreePolyMesh(_mesh);
		_mesh = nullptr;
		
		this->_disposed = true;
	}
}

RecastManaged::Recast::PolyMesh::~PolyMesh()
{
	this->!PolyMesh();
}

rcPolyMesh* RecastManaged::Recast::PolyMesh::GetPointer()
{
	return this->_mesh;
}

#pragma region Verts
void RecastManaged::Recast::PolyMesh::Verts::set(unsigned short* value)
{
	_mesh->verts = value;
}

unsigned short* RecastManaged::Recast::PolyMesh::Verts::get()
{
	return _mesh->verts;
}
#pragma endregion


#pragma region Polys
void RecastManaged::Recast::PolyMesh::Polys::set(unsigned short* value)
{
	_mesh->polys = value;
}

unsigned short* RecastManaged::Recast::PolyMesh::Polys::get()
{
	return _mesh->polys;
}
#pragma endregion


#pragma region Regs
void RecastManaged::Recast::PolyMesh::Regs::set(unsigned short* value)
{
	_mesh->regs = value;
}

unsigned short* RecastManaged::Recast::PolyMesh::Regs::get()
{
	return _mesh->regs;
}
#pragma endregion


#pragma region Flags
void RecastManaged::Recast::PolyMesh::Flags::set(unsigned short* value)
{
	_mesh->flags = value;
}

unsigned short* RecastManaged::Recast::PolyMesh::Flags::get()
{
	return _mesh->flags;
}
#pragma endregion


#pragma region Areas
void RecastManaged::Recast::PolyMesh::Areas::set(unsigned char* value)
{
	_mesh->areas = value;
}

unsigned char* RecastManaged::Recast::PolyMesh::Areas::get()
{
	return _mesh->areas;
}
#pragma endregion


#pragma region NVerts
void RecastManaged::Recast::PolyMesh::NVerts::set(int value)
{
	_mesh->nverts = value;
}

int RecastManaged::Recast::PolyMesh::NVerts::get()
{
	return _mesh->nverts;
}
#pragma endregion


#pragma region NPolys
void RecastManaged::Recast::PolyMesh::NPolys::set(int value)
{
	_mesh->npolys = value;
}

int RecastManaged::Recast::PolyMesh::NPolys::get()
{
	return _mesh->npolys;
}
#pragma endregion


#pragma region NVP
void RecastManaged::Recast::PolyMesh::NVP::set(int value)
{
	_mesh->nvp = value;
}

int RecastManaged::Recast::PolyMesh::NVP::get()
{
	return _mesh->nvp;
}
#pragma endregion


#pragma region CellSize
void RecastManaged::Recast::PolyMesh::CellSize::set(float value)
{
	_mesh->cs = value;
}

float RecastManaged::Recast::PolyMesh::CellSize::get()
{
	return _mesh->cs;
}
#pragma endregion


#pragma region CellHeight
void RecastManaged::Recast::PolyMesh::CellHeight::set(float value)
{
	_mesh->ch = value;
}

float RecastManaged::Recast::PolyMesh::CellHeight::get()
{
	return _mesh->ch;
}
#pragma endregion


#pragma region BMin
void RecastManaged::Recast::PolyMesh::BMin::set(RecastManaged::Tools::Math::Vector3^ value)
{
	_mesh->bmin[0] = value->X;
	_mesh->bmin[1] = value->Y;
	_mesh->bmin[2] = value->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Recast::PolyMesh::BMin::get()
{
	return Tools::Math::Vector3::FromFloatPointer(_mesh->bmin);
}
#pragma endregion


#pragma region BMax
void RecastManaged::Recast::PolyMesh::BMax::set(RecastManaged::Tools::Math::Vector3^ value)
{
	_mesh->bmax[0] = value->X;
	_mesh->bmax[1] = value->Y;
	_mesh->bmax[2] = value->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Recast::PolyMesh::BMax::get()
{
	return Tools::Math::Vector3::FromFloatPointer(_mesh->bmax);
}
#pragma endregion
