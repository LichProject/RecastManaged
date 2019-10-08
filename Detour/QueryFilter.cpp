#include "QueryFilter.h";

RecastManaged::Detour::QueryFilter::QueryFilter(unsigned short includeFlags, unsigned short excludeFlags)
{
	this->_filter = new dtQueryFilter();
	this->IncludeFlags = includeFlags;
	this->ExcludeFlags = excludeFlags;
}

RecastManaged::Detour::QueryFilter::QueryFilter()
{
	this->_filter = new dtQueryFilter();
}

RecastManaged::Detour::QueryFilter::!QueryFilter()
{
	if (!this->_disposed)
	{
		delete _filter;
		_filter = nullptr;
	}
}

float RecastManaged::Detour::QueryFilter::GetAreaCost(unsigned char areaId)
{
	return this->_filter->getAreaCost(areaId);
}

void RecastManaged::Detour::QueryFilter::SetAreaCost(unsigned char areaId, float cost)
{
	_filter->setAreaCost(areaId, cost);
}
