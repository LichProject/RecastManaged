#include "../Unmanaged/Recast/Recast.h"
#include "CompactCell.h"

RecastManaged::Recast::CompactCell::CompactCell(rcCompactCell* cell, bool* destructWithMe)
{
	this->_cell = cell;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::CompactCell::~CompactCell()
{
	this->!CompactCell();
}

RecastManaged::Recast::CompactCell::!CompactCell()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _cell;
		_cell = nullptr;
		
		this->_disposed = true;
	}
}

rcCompactCell* RecastManaged::Recast::CompactCell::GetPointer()
{
	return this->_cell;
}

#pragma region Index
unsigned int RecastManaged::Recast::CompactCell::Index::get()
{
	return _cell->index;
}

void RecastManaged::Recast::CompactCell::Index::set(unsigned int value)
{
	_cell->index = value;
}
#pragma endregion


#pragma region Count
unsigned int RecastManaged::Recast::CompactCell::Count::get()
{
	return _cell->count;
}

void RecastManaged::Recast::CompactCell::Count::set(unsigned int value)
{
	_cell->count = value;
}
#pragma endregion
