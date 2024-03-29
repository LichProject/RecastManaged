#include "RecastManaged.h"

bool RecastManaged::Recast::Recast::BuildCompactHeightfield(int walkableHeight, int walkableClimb, Heightfield^ hf,
                                                            CompactHeightfield^% chf)
{
	chf = gcnew CompactHeightfield();
	return rcBuildCompactHeightfield(_context, walkableHeight, walkableClimb, *hf->GetPointer(), *chf->GetPointer());
}

bool RecastManaged::Recast::Recast::BuildHeightfieldLayers(int walkableHeight, int borderSize, CompactHeightfield^ chf,
                                                           HeightfieldLayerSet^% lset)
{
	lset = gcnew HeightfieldLayerSet();
	return rcBuildHeightfieldLayers(_context, *chf->GetPointer(), borderSize, walkableHeight, *lset->GetPointer());
}

bool RecastManaged::Recast::Recast::CreateHeightfield(int width, int height, array<float>^ bmin, array<float>^ bmax,
                                                      float cs, float ch, Heightfield^% hf)
{
	const pin_ptr<float> pBMin = &bmin[0];
	const pin_ptr<float> pBMax = &bmax[0];

	hf = gcnew Heightfield();
	return rcCreateHeightfield(_context, *hf->GetPointer(), width, height, pBMin, pBMax, cs, ch);
}

bool RecastManaged::Recast::Recast::CreateHeightfield(int width, int height, Tools::Math::Vector3^ bmin,
                                                      Tools::Math::Vector3^ bmax, float cs, float ch, Heightfield^% hf)
{
	const pin_ptr<float> pBMax = &bmax->X;
	const pin_ptr<float> pBMin = &bmin->X;

	hf = gcnew Heightfield();
	return rcCreateHeightfield(_context, *hf->GetPointer(), width, height, pBMin, pBMax, cs, ch);
}

bool RecastManaged::Recast::Recast::ErodeWalkableArea(int radius, CompactHeightfield^ chf)
{
	return rcErodeWalkableArea(_context, radius, *chf->GetPointer());
}

void RecastManaged::Recast::Recast::FilterLedgeSpans(int walkableHeight, int walkableClimb, Heightfield^ solid)
{
	rcFilterLedgeSpans(_context, walkableHeight, walkableClimb, *solid->GetPointer());
}

void RecastManaged::Recast::Recast::FilterLowHangingWalkableObstacles(int walkableClimb, Heightfield^ solid)
{
	rcFilterLowHangingWalkableObstacles(_context, walkableClimb, *solid->GetPointer());
}

void RecastManaged::Recast::Recast::FilterWalkableLowHeightSpans(int walkableHeight, Heightfield^ solid)
{
	rcFilterWalkableLowHeightSpans(_context, walkableHeight, *solid->GetPointer());
}

void RecastManaged::Recast::Recast::MarkConvexPolyArea(array<float>^ verts, int nverts, float heightMin,
                                                       float heightMax, int area, CompactHeightfield^ chf)
{
	const pin_ptr<float> pinVerts = &verts[0];
	rcMarkConvexPolyArea(_context, pinVerts, nverts, heightMin, heightMax, (unsigned char)area, *chf->GetPointer());
}

bool RecastManaged::Recast::Recast::RasterizeTriangles(array<float>^ verts, int* tris, int ntris,
                                                       array<unsigned char>^ areas, Heightfield^ solid,
                                                       int flagMergeThr)
{
	const pin_ptr<float> pVerts = &verts[0];
	const pin_ptr<unsigned char> pAreas = &areas[0];

	return rcRasterizeTriangles(_context, pVerts, verts->Length, tris, pAreas, ntris, *solid->GetPointer(),
	                            flagMergeThr);
}

void RecastManaged::Recast::Recast::MarkWalkableTriangles(const float walkableSlopeAngle, const array<float>^ verts,
                                                          int nv, int* tris, int nt, array<unsigned char>^% areas)
{
	const pin_ptr<const float> pVerts = &verts[0];
	const pin_ptr<unsigned char> pAreas = &areas[0];

	rcMarkWalkableTriangles(_context, walkableSlopeAngle, pVerts, nv, tris, nt, pAreas);
}
