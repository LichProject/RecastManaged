#include "TileReference.h"

RecastManaged::Detour::TileReference::TileReference(unsigned id)
{
	this->Id = id;
}

System::String^ RecastManaged::Detour::TileReference::ToString()
{
	return this->Id.ToString();
}
