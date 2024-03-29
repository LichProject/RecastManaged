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

	const pin_ptr<float> pinCenter = &center->X;
	const pin_ptr<float> pinExtents = &extents->X;
	const pin_ptr<float> pinNearestPt = &nearestPt->X;

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
	unsigned* pathStartToEnd = new unsigned[maxPathSize * 2];

	int pathCount;

	const pin_ptr<float> pinStartPos = &startPos->X;
	const pin_ptr<float> pinEndPos = &endPos->X;

	auto const status = this->_query->findPath(startRef->Id, endRef->Id, pinStartPos,
	                                           pinEndPos, filter->GetPointer(),
	                                           pathStartToEnd,
	                                           &pathCount, maxPathSize);

	result = gcnew array<PolygonReference^>(pathCount);

	for (int i = 0; i < pathCount; i++)
	{
		result[i] = gcnew PolygonReference(i[pathStartToEnd]);
	}

	delete[] pathStartToEnd;

	return gcnew Status(status);
}


RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::QueryPolygons(Tools::Math::Vector3^ center,
                                                                                  Tools::Math::Vector3^ extents,
                                                                                  QueryFilter^ filter, int maxPolys,
                                                                                  array<PolygonReference^>^% result)
{
	unsigned* polys = new unsigned[maxPolys * 2];

	int maxPolysCount;

	const pin_ptr<float> pinCenter = &center->X;
	const pin_ptr<float> pinExtents = &extents->X;

	auto const status = this->_query->queryPolygons(pinCenter, pinExtents,
	                                                filter->GetPointer(), polys, &maxPolysCount,
	                                                maxPolys);

	result = gcnew array<PolygonReference^>(maxPolysCount);

	for (int i = 0; i < maxPolysCount; i++)
	{
		result[i] = gcnew PolygonReference(i[polys]);
	}

	delete[] polys;

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindStraightPath(Tools::Math::Vector3^ startPos,
                                                                                     Tools::Math::Vector3^ endPos,
                                                                                     array<PolygonReference^>^ path,
                                                                                     int maxStraightPathSize,
                                                                                     array<Tools::Math::Vector3^>^%
                                                                                     points,
                                                                                     array<StraightPathFlags>^%
                                                                                     straightPathFlags,
                                                                                     array<PolygonReference^>^%
                                                                                     straightPathRef)
{
	const pin_ptr<float> pStartPos = &startPos->X;
	const pin_ptr<float> pEndPos = &endPos->X;

	const int pathLength = path->Length;

	dtPolyRef* uPath = new dtPolyRef[pathLength];
	for (int i = 0; i < pathLength; ++i)
	{
		uPath[i] = path[i]->Id;
	}

	const auto sPath = new float[maxStraightPathSize * 3];
	const auto sPathFlags = new unsigned char[maxStraightPathSize];
	const auto sPathRefs = new unsigned[maxStraightPathSize];

	int sPathCount;

	const auto status = this->_query->findStraightPath(pStartPos, pEndPos, uPath, pathLength, sPath, sPathFlags, sPathRefs,
	                                             &sPathCount, maxStraightPathSize, 0);

	points = gcnew array<Tools::Math::Vector3^>(sPathCount);
	straightPathFlags = gcnew array<StraightPathFlags>(sPathCount);
	straightPathRef = gcnew array<PolygonReference^>(sPathCount);

	for (int i = 0; i < sPathCount; ++i)
	{
		float* point = sPath + i * 3;
		points[i] = gcnew Tools::Math::Vector3(*point, *(point + 1), *(point + 2));
		straightPathFlags[i] = (StraightPathFlags)*(sPathFlags + i);
		straightPathRef[i] = gcnew PolygonReference(*(sPathRefs + i));
	}

	delete[] sPath;
	delete[] sPathFlags;
	delete[] sPathRefs;

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::Raycast(PolygonReference^ startRef,
                                                                            Tools::Math::Vector3^ startPos,
                                                                            Tools::Math::Vector3^ endPos,
                                                                            QueryFilter^ filter, int maxPolys,
                                                                            array<PolygonReference^>^% result,
                                                                            float% t,
                                                                            Tools::Math::Vector3^% hitNormal)
{
	const auto path = new dtPolyRef[maxPolys * 2];

	hitNormal = gcnew Tools::Math::Vector3(0, 0, 0);

	const pin_ptr<float> pHitNormal = &hitNormal->X;
	const pin_ptr<float> startPosPin = &startPos->X;
	const pin_ptr<float> endPosPin = &endPos->X;
	const pin_ptr<float> pT = &t;
	
	int length;

	auto const status = this->_query->raycast(startRef->Id, startPosPin, endPosPin, filter->GetPointer(), pT,
	                                          pHitNormal, path, &length, maxPolys);

	auto const polyRefs = result = gcnew array<PolygonReference^>(length);
	if (length > 0)
	{
		const pin_ptr<PolygonReference^> polyRefPtr = &polyRefs[0];
		memcpy(polyRefPtr, &path, length);
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
	hitPos = gcnew Tools::Math::Vector3(0, 0, 0);
	hitNormal = gcnew Tools::Math::Vector3(0, 0, 0);
	
	const pin_ptr<float> pCenterPos = &centerPos->X;
	const pin_ptr<float> pHitPos = &hitPos->X;
	const pin_ptr<float> pHitNormal = &hitNormal->X;
	const pin_ptr<float> pResult = &result;
	
	auto const status = this->_query->findDistanceToWall(centerRef->Id, pCenterPos, maxRadius, filter->GetPointer(), pResult, pHitPos, pHitNormal);
	return gcnew Status(status);
}

static float frand()
{
	return (float)rand() / (float)RAND_MAX;
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMeshQuery::FindRandomPointAroundCircle(
	PolygonReference^ startRef, Tools::Math::Vector3^ centerPos, float maxRadius, QueryFilter^ filter,
	PolygonReference^% randomRef, Tools::Math::Vector3^% randomPoint)
{
	const pin_ptr<float> pCenterPos = &centerPos->X;
	const pin_ptr<float> pRandomPt = &randomPoint->X;
	
	unsigned id;
	auto const status = this->_query->findRandomPointAroundCircle(startRef->Id, pCenterPos, maxRadius, filter->GetPointer(), frand, &id, pRandomPt);
	
	randomRef = gcnew PolygonReference(id);

	return gcnew Status(id);
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
