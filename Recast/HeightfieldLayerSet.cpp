#include "HeightfieldLayerSet.h"

RecastManaged::Recast::HeightfieldLayerSet::HeightfieldLayerSet()
{
	this->_lset = rcAllocHeightfieldLayerSet();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Recast::HeightfieldLayerSet::HeightfieldLayerSet(rcHeightfieldLayerSet* lset, bool* destructWithMe)
{
	this->_lset = lset;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::HeightfieldLayerSet::!HeightfieldLayerSet()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		rcFreeHeightfieldLayerSet(_lset);
		_lset = nullptr;
		
		this->_disposed = true;
	}
}

RecastManaged::Recast::HeightfieldLayerSet::~HeightfieldLayerSet()
{
	this->!HeightfieldLayerSet();
}

rcHeightfieldLayerSet* RecastManaged::Recast::HeightfieldLayerSet::GetPointer()
{
	return this->_lset;
}

