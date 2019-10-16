#include "NavMeshData.h"
#include "../Unmanaged/Detour/DetourNode.h"

RecastManaged::Detour::NavMeshData::NavMeshData(array<unsigned char>^ navData, int startIndex, int length)
{
	this->NavDataSize = length;
	this->NavData = (unsigned char*)dtAlloc(length, DT_ALLOC_PERM);
	System::Runtime::InteropServices::Marshal::Copy(navData, startIndex, System::IntPtr(this->NavData), length);
	this->_disposed = false;
	this->OwnsData = true;
}

RecastManaged::Detour::NavMeshData::NavMeshData(unsigned char* navData, int navDataSize)
{
	this->NavData = navData;
	this->NavDataSize = navDataSize;
	this->_disposed = false;
	this->OwnsData = true;
}

RecastManaged::Detour::NavMeshData::~NavMeshData()
{
	this->!NavMeshData();
}

RecastManaged::Detour::NavMeshData::!NavMeshData()
{
	//if (!this->_disposed) // TODO old (new uncomment)
	//{
	//	unsigned char* navData = NavData;
	//	if (navData && this->OwnsData)
	//	{
	//		dtFree(navData);
	//		NavData = nullptr;
	//		
	//		this->_disposed = true;
	//	}
	//}
}

array<unsigned char>^ RecastManaged::Detour::NavMeshData::GetNavData()
{
	const auto buffer = gcnew array<unsigned char>(this->NavDataSize);
	this->GetNavData(buffer, 0);
	return buffer;
}

void RecastManaged::Detour::NavMeshData::GetNavData(array<unsigned char>^ buffer, int start)
{
	System::Runtime::InteropServices::Marshal::Copy(System::IntPtr(this->NavData), buffer, start,
	                                                this->NavDataSize);
}
