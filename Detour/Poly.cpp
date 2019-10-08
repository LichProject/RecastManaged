#include "Poly.h"

RecastManaged::Detour::Poly::Poly(dtPoly* p, bool* destructWithMe)
{
	this->_p = p;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::Poly::Poly()
{
	this->_p = new dtPoly();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::Poly::~Poly()
{
	this->!Poly();
}

RecastManaged::Detour::Poly::!Poly()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _p;
		_p = nullptr;
		
		this->_disposed = true;
	}
}

dtPoly* RecastManaged::Detour::Poly::GetPointer()
{
	return this->_p;
}

unsigned short RecastManaged::Detour::Poly::GetVert(int index)
{
	return _p->verts[index];
}
