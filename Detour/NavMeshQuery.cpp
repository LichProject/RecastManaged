#include "NavMeshQuery.h"

RecastManaged::Detour::NavMeshQuery::NavMeshQuery(dtNavMeshQuery* query, bool* destructWithMe)
{
	this->SetTileLoaderFunction(nullptr);
	this->_query = query;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshQuery::NavMeshQuery()
{
	this->_query = dtAllocNavMeshQuery();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::NavMeshQuery::!NavMeshQuery()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		dtFreeNavMeshQuery(_query);
		_query = nullptr;

		this->_disposed = true;
	}
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::Init(NavMesh^ mesh, int maxNodes)
{
	return gcnew Status(this->_query->init(mesh->GetPointer(), maxNodes));
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindNearestPolygon(Tools::Math::Vector3^ center,
                                                                                       Tools::Math::Vector3^ extents,
                                                                                       QueryFilter^ filter,
                                                                                       Tools::Math::Vector3^% nearestPt,
                                                                                       PolygonReference^% result)
{
	nearestPt = gcnew Tools::Math::Vector3(0, 0, 0);
	unsigned id;

	pin_ptr<float> pinCenter = &center->X;
	pin_ptr<float> pinExtents = &extents->X;
	pin_ptr<float> pinNearestPt = &nearestPt->X;

	const unsigned status = this->_query->findNearestPoly(pinCenter, pinExtents, filter->GetPointer(), &id,
	                                                      pinNearestPt);

	result = gcnew PolygonReference(id);

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindPath(PolygonReference^ startRef,
                                                                             PolygonReference^ endRef,
                                                                             Tools::Math::Vector3^ startPos,
                                                                             Tools::Math::Vector3^ endPos,
                                                                             QueryFilter^ filter,
                                                                             int maxPathSize,
                                                                             array<PolygonReference^>^% result)
{
	unsigned* pathStartToEnd = new unsigned[maxPathSize > 0x3FFFFFFF ? -1 : maxPathSize << 2];

	int pathCount;

	pin_ptr<float> pinStartPos = &startPos->X;
	pin_ptr<float> pinEndPos = &endPos->X;

	auto const status = this->_query->findPath(startRef->Id, endRef->Id, pinStartPos,
	                                           pinEndPos, filter->GetPointer(),
	                                           pathStartToEnd,
	                                           &pathCount, maxPathSize);

	result = gcnew array<PolygonReference^>(pathCount);

	for (int i = 0; i < pathCount; i++)
	{
		result[i] = gcnew PolygonReference(i[pathStartToEnd]);
	}

	pathStartToEnd = nullptr;

	return gcnew Status(status);
}


RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::QueryPolygons(Tools::Math::Vector3^ center,
                                                                                  Tools::Math::Vector3^ extents,
                                                                                  QueryFilter^ filter, int maxPolys,
                                                                                  array<PolygonReference^>^% result)
{
	unsigned* polys = new unsigned[maxPolys > 0x3FFFFFFF ? -1 : maxPolys * 2];

	int maxPolysCount;

	pin_ptr<float> pinCenter = &center->X;
	pin_ptr<float> pinExtents = &extents->X;

	auto const status = this->_query->queryPolygons(pinCenter, pinExtents,
	                                                filter->GetPointer(), polys, &maxPolysCount,
	                                                maxPolys);

	result = gcnew array<PolygonReference^>(maxPolysCount);

	for (int i = 0; i < maxPolysCount; i++)
	{
		result[i] = gcnew PolygonReference(i[polys]);
	}

	polys = nullptr;

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindStraightPath(Tools::Math::Vector3^ startPos,
                                                                                     Tools::Math::Vector3^ endPos,
                                                                                     array<PolygonReference^>^ polyPath,
                                                                                     int maxStraightPathSize,
                                                                                     array<Tools::Math::Vector3^>^%
                                                                                     points,
                                                                                     array<StraightPathFlags>^%
                                                                                     straightPathFlags,
                                                                                     array<PolygonReference^>^%
                                                                                     straightPathRef)
{
	return gcnew Status(0);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::Raycast(PolygonReference^ startRef,
                                                                            Tools::Math::Vector3^ startPos,
                                                                            Tools::Math::Vector3^ endPos,
                                                                            QueryFilter^ filter, int maxPolys,
                                                                            array<PolygonReference^>^% result,
                                                                            float% t,
                                                                            Tools::Math::Vector3^% hitNormal)
{
	const auto path = new dtPolyRef[(unsigned)(maxPolys << 2)];

	const pin_ptr<float> hitNormalPin = &hitNormal->X;
	const pin_ptr<float> startPosPin = &startPos->X;
	const pin_ptr<float> endPosPin = &endPos->X;

	float t2;
	int length;

	auto const status = this->_query->raycast(startRef->Id, startPosPin, endPosPin, filter->GetPointer(), &t2,
	                                          hitNormalPin, path, &length, maxPolys);

	t = t2;

	auto const polyRefs = result = gcnew array<PolygonReference^>(length);
	if (length > 0)
	{
		const pin_ptr<PolygonReference^> polyRefPtr = &polyRefs[0];
		memcpy(polyRefPtr, &path, length << 2);
	}

	delete[] path;
	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindDistanceToWall(PolygonReference^ centerRef,
                                                                                       Tools::Math::Vector3^ centerPos,
                                                                                       float maxRadius,
                                                                                       QueryFilter^ filter,
                                                                                       float% result,
                                                                                       Tools::Math::Vector3^% hitPos,
                                                                                       Tools::Math::Vector3^% hitNormal)
{
	return gcnew Status(0);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindRandomPointAroundCircle(
	PolygonReference^ startRef, Tools::Math::Vector3^ centerPos, float maxRadius, QueryFilter^ filter,
	PolygonReference^% randomRef, Tools::Math::Vector3^% randomPoint)
{
	return gcnew Status(0);
}

void RecastManaged::Detour::NavMeshQuery::SetTileLoaderFunction(LoadTileDelegate^ del)
{
	this->_tileLoaderDel = del;
	if (this->_query != nullptr)
	{
		IntPtr* value = new IntPtr(this->_query);
		GCHandle::FromIntPtr(*value).Free();
	}
	if (del != nullptr)
	{
		void* ptr2 = GCHandle::ToIntPtr(GCHandle::Alloc(this->_tileLoaderDel)).ToPointer();
		dtNavMeshQuery* query2 = this->_query;
	}
}
