#include "CompactSpan.h"
#include "CompactCell.h"

RecastManaged::Recast::CompactSpan::!CompactSpan()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _span;
		_span = nullptr;
		
		this->_disposed = true;
	}
}

RecastManaged::Recast::CompactSpan::CompactSpan(rcCompactSpan* span, bool* destructWithMe)
{
	this->_span = span;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::CompactSpan::~CompactSpan()
{
	this->!CompactSpan();
}

rcCompactSpan* RecastManaged::Recast::CompactSpan::GetPointer()
{
	return this->_span;
}

#pragma region Height
unsigned int RecastManaged::Recast::CompactSpan::Height::get()
{
	return _span->h;
}

void RecastManaged::Recast::CompactSpan::Height::set(unsigned int value)
{
	_span->h = value;
}
#pragma endregion


#pragma region Connections
unsigned int RecastManaged::Recast::CompactSpan::Connections::get()
{
	return _span->con;
}

void RecastManaged::Recast::CompactSpan::Connections::set(unsigned int value)
{
	_span->con = value;
}
#pragma endregion


#pragma region Reg
unsigned short RecastManaged::Recast::CompactSpan::Reg::get()
{
	return _span->reg;
}

void RecastManaged::Recast::CompactSpan::Reg::set(unsigned short value)
{
	_span->reg = value;
}
#pragma endregion


#pragma region Y
unsigned short RecastManaged::Recast::CompactSpan::Y::get()
{
	return _span->y;
}

void RecastManaged::Recast::CompactSpan::Y::set(unsigned short value)
{
	_span->y = value;
}
#pragma endregion
