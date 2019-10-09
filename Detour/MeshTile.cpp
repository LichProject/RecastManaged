#include "MeshTile.h"

RecastManaged::Detour::MeshTile::MeshTile(dtMeshTile* mt, bool* destructWithMe)
{
	this->_mt = mt;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::MeshTile::~MeshTile()
{
	this->!MeshTile();
}

RecastManaged::Detour::MeshTile::!MeshTile()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _mt;
		_mt = nullptr;

		this->_disposed = true;
	}
}

RecastManaged::Detour::OffMeshConnection^ RecastManaged::Detour::MeshTile::GetOffMeshConnection(int index)
{
	if (index >= 0)
	{
		auto const length = this->_mt->header->offMeshConCount;
		if (length <= index)
		{
			return nullptr;
		}

		auto const cons = this->_mt->offMeshCons;
		return gcnew OffMeshConnection(&cons[index], false);
	}

	return nullptr;
}

array<RecastManaged::Detour::OffMeshConnection^>^ RecastManaged::Detour::MeshTile::GetAllOffMeshConnections()
{
	auto const length = _mt->header->offMeshConCount;
	auto const offMeshCons = gcnew array<OffMeshConnection^>(length);

	for (int i = 0; i < length; ++i)
	{
		offMeshCons[i] = gcnew OffMeshConnection(&_mt->offMeshCons[i], false);
	}

	return offMeshCons;
}

RecastManaged::Detour::Poly^ RecastManaged::Detour::MeshTile::GetPoly(int index)
{
	if (index >= 0)
	{
		auto const length = this->_mt->header->polyCount;
		if (length <= index)
		{
			return nullptr;
		}

		auto const polys = this->_mt->polys;
		return gcnew Poly(&polys[index], false);
	}

	return nullptr;
}

array<RecastManaged::Detour::Poly^>^ RecastManaged::Detour::MeshTile::GetAllPolys()
{
	dtMeshTile* mt = this->_mt;

	auto const length = mt->header->polyCount;
	auto const polys = gcnew array<Poly^>(length);

	for (int i = 0; i < length; ++i)
	{
		polys[i] = gcnew Poly(&mt->polys[i], false);
	}

	return polys;
}

RecastManaged::Detour::PolyDetail^ RecastManaged::Detour::MeshTile::GetPolyDetail(int index)
{
	if (index >= 0)
	{
		auto const length = this->_mt->header->detailMeshCount;
		if (length <= index)
		{
			return nullptr;
		}

		auto const polyDetails = this->_mt->detailMeshes;
		return gcnew PolyDetail(&polyDetails[index], false);
	}

	return nullptr;
}

array<RecastManaged::Detour::PolyDetail^>^ RecastManaged::Detour::MeshTile::GetAllDetailPolys()
{
	auto const length = _mt->header->detailMeshCount;
	auto const polyDetails = gcnew array<PolyDetail^>(length);

	for (int i = 0; i < length; ++i)
	{
		polyDetails[i] = gcnew PolyDetail(&_mt->detailMeshes[i], false);
	}

	return polyDetails;
}

array<unsigned char>^ RecastManaged::Detour::MeshTile::GetAllDetailIndices()
{
	const auto mt = _mt;
	const auto size = mt->header->detailTriCount;

	const auto detailIndices = gcnew array<unsigned char>(size);
	const auto source = IntPtr(mt->detailTris);

	Marshal::Copy(source, detailIndices, 0, size);

	return detailIndices;
}

array<RecastManaged::Tools::Math::Vector3^>^ RecastManaged::Detour::MeshTile::GetAllVertices()
{
	auto const vertsRaw = this->Verts;
	auto const length = _mt->header->vertCount;
	auto const verts = gcnew array<Tools::Math::Vector3^>(length);

	for (int i = 0; i < length; ++i)
	{
		verts[i] = gcnew Tools::Math::Vector3(vertsRaw[i], vertsRaw[i + 1], vertsRaw[i + 2]);
	}

	return verts;
}

array<RecastManaged::Tools::Math::Vector3^>^ RecastManaged::Detour::MeshTile::GetAllDetailVertices()
{
	auto const detailVertsRaw = this->DetailVerts;
	auto const size = _mt->header->detailVertCount;
	auto const detailVerts = gcnew array<Tools::Math::Vector3^>(size);

	for (int i = 0; i < size; i++)
	{
		detailVerts[i] = gcnew Tools::Math::Vector3(detailVertsRaw[i], detailVertsRaw[i + 1], detailVertsRaw[i + 2]);
	}

	return detailVerts;
}
