#include "PolyDetail.h"

RecastManaged::Detour::PolyDetail::PolyDetail(dtPolyDetail* pd, bool* destructWithMe)
{
	this->_pd = pd;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::PolyDetail::PolyDetail()
{
	this->_pd = new dtPolyDetail();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::PolyDetail::~PolyDetail()
{
	this->!PolyDetail();
}

RecastManaged::Detour::PolyDetail::!PolyDetail()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _pd;
		_pd = nullptr;
		
		this->_disposed = true;
	}
}
