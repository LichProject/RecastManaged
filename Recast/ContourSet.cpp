#include "ContourSet.h"
#include "../Unmanaged/Recast/Recast.h"

RecastManaged::Recast::ContourSet::!ContourSet()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreeContourSet(_cset);
		_cset = nullptr;
		
		this->_disposed = true;
	}
}

RecastManaged::Recast::ContourSet::ContourSet()
{
	this->_cset = rcAllocContourSet();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::ContourSet::ContourSet(rcContourSet* cset, bool* destructWithMe)
{
	this->_cset = cset;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::ContourSet::~ContourSet()
{
	this->!ContourSet();
}

rcContourSet* RecastManaged::Recast::ContourSet::GetPointer()
{
	return this->_cset;
}

#pragma region NConts
int RecastManaged::Recast::ContourSet::NConts::get()
{
	return _cset->nconts;
}

void RecastManaged::Recast::ContourSet::NConts::set(int value)
{
	_cset->nconts = value;
}
#pragma endregion


#pragma region Conts
rcContour* RecastManaged::Recast::ContourSet::Conts::get()
{
	return _cset->conts;
}

void RecastManaged::Recast::ContourSet::Conts::set(rcContour* value)
{
	_cset->conts = value;
}
#pragma endregion
