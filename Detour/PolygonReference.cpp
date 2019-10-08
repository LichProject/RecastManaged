#include "PolygonReference.h"

RecastManaged::Detour::PolygonReference::PolygonReference(unsigned id)
{
	this->Id = id;
}

System::String^ RecastManaged::Detour::PolygonReference::ToString()
{
	return this->Id.ToString();
}
