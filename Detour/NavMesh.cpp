#include "NavMesh.h"

RecastManaged::Detour::NavMesh::NavMesh(dtNavMesh* mesh, bool destructWithMe)
{
	this->_mesh = mesh;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::NavMesh::NavMesh()
{
	this->_mesh = dtNavMesh::dtAllocNavMesh();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::NavMesh::!NavMesh()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		dtFreeNavMesh(_mesh);
		_mesh = nullptr;
	}
}

RecastManaged::Detour::NavMesh::~NavMesh()
{
	this->!NavMesh();
}

dtNavMesh* RecastManaged::Detour::NavMesh::GetPointer()
{
	return this->_mesh;
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::Init(NavMeshData^ data)
{
	const unsigned status = this->_mesh->init(data->NavData, data->NavDataSize, 1);

	if ((status & DT_WRONG_MAGIC) != 0)
	{
		data->OwnsData = false;
	}

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::Init(NavMeshParams^ params)
{
	return gcnew Status(this->_mesh->init(params->GetPointer()));
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::AddTile(NavMeshData^ data, TileReference^% tileRef)
{
	unsigned id;
	auto const status = this->_mesh->addTile(data->NavData, data->NavDataSize, 1, 0, &id);

	tileRef = gcnew TileReference(id);

	if ((status & DT_WRONG_MAGIC) != 0)
	{
		data->OwnsData = false;
	}

	return gcnew Status(status);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::RemoveTile(TileReference^ tileRef)
{
	return gcnew Status(this->_mesh->removeTile(tileRef->Id, nullptr, nullptr));
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::RemoveTile(TileReference^ tileRef, NavMeshData^% data)
{
	unsigned char* navData = nullptr;
	int navDataSize = 0;

	auto const result = gcnew Status(this->_mesh->removeTile(tileRef->Id, &navData, &navDataSize));
	data = gcnew NavMeshData(navData, navDataSize);

	return result;
}

RecastManaged::Detour::MeshTile^ RecastManaged::Detour::NavMesh::GetTileAt(int x, int y, int layer)
{
	dtMeshTile* ptr = const_cast<dtMeshTile*>(this->_mesh->getTileAt(x, y, layer));
	return ptr != nullptr ? gcnew MeshTile(ptr, false) : nullptr;
}

RecastManaged::Detour::TileReference^ RecastManaged::Detour::NavMesh::GetTileRefAt(int x, int y, int layer)
{
	return gcnew TileReference(this->_mesh->getTileRefAt(x, y, layer));
}

RecastManaged::Detour::TileReference^ RecastManaged::Detour::NavMesh::GetTileRef(MeshTile^ tile)
{
	return gcnew TileReference(this->_mesh->getTileRef(tile->GetPointer()));
}

int RecastManaged::Detour::NavMesh::GetMaxTiles()
{
	return this->_mesh->getMaxTiles();
}

RecastManaged::Detour::MeshTile^ RecastManaged::Detour::NavMesh::GetTile(int i)
{
	const auto tile = _mesh->getTile(i);
	return tile != nullptr ? gcnew MeshTile(tile, false) : nullptr;
}

int RecastManaged::Detour::NavMesh::GetTileStateSize(MeshTile^ tile)
{
	return this->_mesh->getTileStateSize(tile->GetPointer());
}

//array<unsigned char>^ RecastManaged::Detour::NavMesh::StoreTileState(MeshTile^ tile, int maxDataSize)
//{
//	auto arr = gcnew array<unsigned char>(maxDataSize);
//	//array<unsigned char>^ *arr2 = arr;
//
//	unsigned char* BigCheese = new unsigned char[maxDataSize];
//	
//	return (this->_mesh->storeTileState(tile->GetPointer(), BigCheese, maxDataSize) == int(StatusDetailFlag::Failure))
//		       ? nullptr
//		       : arr;
//}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::RestoreTileState(MeshTile^ tile,
                                                                                array<unsigned char>^ data)
{
	const pin_ptr<unsigned char> pinData = &data[0];
	return gcnew Status(this->_mesh->restoreTileState(tile->GetPointer(), pinData, data->Length));
}

void RecastManaged::Detour::NavMesh::SetPolyFlags(PolygonReference^ polyRef, unsigned short flags)
{
	this->_mesh->setPolyFlags(polyRef->Id, flags);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::GetPolyFlags(PolygonReference^ polyRef,
                                                                            unsigned short^% flags)
{
	unsigned short resultFlags;
	const auto result = this->_mesh->getPolyFlags(polyRef->Id, &resultFlags);

	flags = resultFlags;
	return gcnew Status(result);
}

void RecastManaged::Detour::NavMesh::SetPolyArea(PolygonReference^ polyRef, unsigned char area)
{
	this->_mesh->setPolyArea(polyRef->Id, area);
}

RecastManaged::Detour::Status^ RecastManaged::Detour::NavMesh::GetPolyArea(PolygonReference^ polyRef,
                                                                           unsigned char^% area)
{
	unsigned char resultArea;
	const auto result = this->_mesh->getPolyArea(polyRef->Id, &resultArea);

	area = resultArea;
	return gcnew Status(result);
}

RecastManaged::Detour::PolygonReference^ RecastManaged::Detour::NavMesh::EncodePolyId(unsigned salt, unsigned it,
                                                                                      unsigned ip)
{
	return gcnew PolygonReference(this->_mesh->encodePolyId(salt, it, ip));
}

void RecastManaged::Detour::NavMesh::DecodePolyId(PolygonReference^ polyRef, unsigned^% salt, unsigned^% it,
                                                  unsigned^% ip)
{
	unsigned* saltCopy;
	unsigned* itCopy;
	unsigned* ipCopy;

	this->_mesh->decodePolyId(polyRef->Id, *saltCopy, *itCopy, *ipCopy);

	salt = *saltCopy;
	it = *itCopy;
	ip = *ipCopy;
}

unsigned RecastManaged::Detour::NavMesh::DecodePolyIdSalt(PolygonReference^ polyRef)
{
	return this->_mesh->decodePolyIdSalt(polyRef->Id);
}

unsigned RecastManaged::Detour::NavMesh::DecodePolyIdTile(PolygonReference^ polyRef)
{
	return this->_mesh->decodePolyIdTile(polyRef->Id);
}

unsigned RecastManaged::Detour::NavMesh::DecodePolyIdPoly(PolygonReference^ polyRef)
{
	return this->_mesh->decodePolyIdPoly(polyRef->Id);
}

Collections::Generic::List<RecastManaged::Detour::MeshTile^>^ RecastManaged::Detour::NavMesh::GetAllTiles()
{
	if (this->_mesh == nullptr)
	{
		return nullptr;
	}

	auto list = gcnew Collections::Generic::List<MeshTile^>();

	const dtNavMesh* mesh = this->_mesh;
	const int size = mesh->getMaxTiles();

	for (int i = 0; i < size; i++)
	{
		const auto tile = mesh->getTile(i);
		if (tile != nullptr && tile->verts != nullptr)
		{
			list->Add(gcnew MeshTile(const_cast<dtMeshTile*>(tile), false));
		}
	}

	return list;
}

RecastManaged::Detour::NavMesh^ RecastManaged::Detour::NavMesh::LoadAll(String^ path)
{
	auto str = (char*)(void*)Marshal::StringToHGlobalAnsi(path);
	auto mesh = dtNavMesh::loadAll(str);

	Marshal::FreeHGlobal((IntPtr)str);
	return gcnew NavMesh(mesh, true);
}
