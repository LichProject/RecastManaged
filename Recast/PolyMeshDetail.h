#pragma once
#include "PolyMesh.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class PolyMeshDetail
		{
			rcPolyMeshDetail* _mesh;
			bool _destructWithMe;
			bool _disposed;

		public:
			PolyMeshDetail();

			PolyMeshDetail(rcPolyMeshDetail* mesh, bool* destructWithMe);

			~PolyMeshDetail();

			!PolyMeshDetail();

			rcPolyMeshDetail* GetPointer();

			virtual property int NTris
			{
				int get();
				void set(int value);
			}

			virtual property int NVerts
			{
				int get();
				void set(int value);
			}

			virtual property int NMeshes
			{
				int get();
				void set(int value);
			}

			virtual property unsigned char* Tris
			{
				unsigned char* get();
				void set(unsigned char* value);
			}

			virtual property float* Verts
			{
				float* get();
				void set(float* value);
			}

			virtual property unsigned* Meshes
			{
				unsigned* get();
				void set(unsigned* value);
			}
		};
	}

}