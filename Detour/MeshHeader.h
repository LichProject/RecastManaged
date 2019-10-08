#pragma once
#include "NavMeshParams.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class MeshHeader
		{
			dtMeshHeader* _mh;
			bool _destructWithMe;
			bool _disposed;

		public:
			MeshHeader(dtMeshHeader* mh, bool* destructWithMe);

			MeshHeader();

			~MeshHeader();

			!MeshHeader();

			dtMeshHeader* GetPointer();

			virtual property int X
			{
				int get();
				void set(int value);
			}


			virtual property int Y
			{
				int get();
				void set(int value);
			}


			virtual property int Magic
			{
				int get();
				void set(int value);
			}


			virtual property int Version
			{
				int get();
				void set(int value);
			}


			virtual property int PolyCount
			{
				int get();
				void set(int value);
			}


			virtual property int VertCount
			{
				int get();
				void set(int value);
			}


			virtual property int MaxLinkCount
			{
				int get();
				void set(int value);
			}


			virtual property int DetailMeshCount
			{
				int get();
				void set(int value);
			}


			virtual property int DetailVertCount
			{
				int get();
				void set(int value);
			}


			virtual property int DetailTriCount
			{
				int get();
				void set(int value);
			}


			virtual property int BVNodeCount
			{
				int get();
				void set(int value);
			}


			virtual property int OffMeshConCount
			{
				int get();
				void set(int value);
			}


			virtual property int OffMeshBase
			{
				int get();
				void set(int value);
			}


			virtual property float WalkableHeight
			{
				float get();
				void set(float value);
			}


			virtual property float WalkableRadius
			{
				float get();
				void set(float value);
			}


			virtual property float WalkableClimb
			{
				float get();
				void set(float value);
			}


			virtual property float BVQuantFactor
			{
				float get();
				void set(float value);
			}
		};
	}
}
