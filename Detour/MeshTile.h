#pragma once
#include "NavMeshData.h"
#include "TileFlags.h"
#include "OffMeshConnection.h"
#include "MeshHeader.h"
#include "Poly.h"
#include "PolyDetail.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class MeshTile
		{
			dtMeshTile* _mt;
			bool _destructWithMe;
			bool _disposed;

		public:
			MeshTile(dtMeshTile* mt, bool* destructWithMe);

			~MeshTile();

			!MeshTile();

			dtMeshTile* GetPointer()
			{
				return this->_mt;
			}

			virtual property unsigned Salt
			{
				unsigned get()
				{
					return _mt->salt;
				}

				void set(unsigned value)
				{
					_mt->salt = value;
				}
			}

			virtual property unsigned LinksFreeList
			{
				unsigned get()
				{
					return _mt->linksFreeList;
				}

				void set(unsigned value)
				{
					_mt->linksFreeList = value;
				}
			}

			virtual property MeshHeader^ Header
			{
				MeshHeader^ get()
				{
					return gcnew MeshHeader(_mt->header, false);
				}

				void set(MeshHeader^ value)
				{
					_mt->header = value->GetPointer();
				}
			}

			virtual property dtPoly* Polys
			{
				dtPoly* get()
				{
					return _mt->polys;
				}

				void set(dtPoly* value)
				{
					_mt->polys = value;
				}
			}

			virtual property float* Verts
			{
				float* get()
				{
					return _mt->verts;
				}

				void set(float* value)
				{
					_mt->verts = value;
				}
			}

			virtual property dtLink* Links
			{
				dtLink* get()
				{
					return _mt->links;
				}

				void set(dtLink* value)
				{
					_mt->links = value;
				}
			}

			virtual property dtPolyDetail* DetailMeshes
			{
				dtPolyDetail* get()
				{
					return _mt->detailMeshes;
				}

				void set(dtPolyDetail* value)
				{
					_mt->detailMeshes = value;
				}
			}

			virtual property float* DetailVerts
			{
				float* get()
				{
					return _mt->detailVerts;
				}

				void set(float* value)
				{
					_mt->detailVerts = value;
				}
			}

			virtual property unsigned char* DetailTris
			{
				unsigned char* get()
				{
					return _mt->detailTris;
				}

				void set(unsigned char* value)
				{
					_mt->detailTris = value;
				}
			}

			virtual property dtBVNode* BVTree
			{
				dtBVNode* get()
				{
					return _mt->bvTree;
				}

				void set(dtBVNode* value)
				{
					_mt->bvTree = value;
				}
			}

			virtual property dtOffMeshConnection* OffMeshCons
			{
				dtOffMeshConnection* get()
				{
					return _mt->offMeshCons;
				}

				void set(dtOffMeshConnection* value)
				{
					_mt->offMeshCons = value;
				}
			}

			virtual property NavMeshData^ Data
			{
				NavMeshData^ get()
				{
					return gcnew NavMeshData(_mt->data, _mt->dataSize);
				}

				void set(NavMeshData^ value)
				{
					_mt->data = value->NavData;
					_mt->dataSize = value->NavDataSize;
					value->OwnsData = false;
				}
			}

			virtual property TileFlags Flags
			{
				TileFlags get()
				{
					return TileFlags(_mt->flags);
				}

				void set(TileFlags value)
				{
					_mt->flags = int(value);
				}
			}

			virtual property MeshTile^ Next
			{
				MeshTile^ get()
				{
					return gcnew MeshTile(_mt->next, false);
				}

				void set(MeshTile^ value)
				{
					_mt->next = value->GetPointer();
				}
			}

			OffMeshConnection^ GetOffMeshConnection(int index);

			array<OffMeshConnection^>^ GetAllOffMeshConnections();

			Poly^ GetPoly(int index);

			array<Poly^>^ GetAllPolys();

			PolyDetail^ GetPolyDetail(int index);

			array<PolyDetail^>^ GetAllDetailPolys();

			array<unsigned char>^ GetAllDetailIndices();

			array<float>^ GetAllVertices();

			array<float>^ GetAllDetailVertices();
		};
	}
}
