#pragma once
#include "../Unmanaged/Recast/Recast.h"
#include "../Tools/Math/Vector3.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class PolyMesh
		{
			rcPolyMesh* _mesh;
			bool _destructWithMe;
			bool _disposed;

		public:
			PolyMesh();

			PolyMesh(rcPolyMesh* mesh, bool* destructWithMe);

			!PolyMesh();

			~PolyMesh();

			rcPolyMesh* GetPointer();

			virtual property RecastManaged::Tools::Math::Vector3^ BMax
			{
				RecastManaged::Tools::Math::Vector3^ get();
				void set(RecastManaged::Tools::Math::Vector3^ value);
			}

			virtual property RecastManaged::Tools::Math::Vector3^ BMin
			{
				RecastManaged::Tools::Math::Vector3^ get();
				void set(RecastManaged::Tools::Math::Vector3^ value);
			}

			virtual property float CellHeight
			{
				float get();
				void set(float value);
			}

			virtual property float CellSize
			{
				float get();
				void set(float value);
			}

			virtual property int NVP
			{
				int get();
				void set(int value);
			}

			virtual property int NPolys
			{
				int get();
				void set(int value);
			}

			virtual property int NVerts
			{
				int get();
				void set(int value);
			}

			virtual property unsigned char* Areas
			{
				unsigned char* get();
				void set(unsigned char* value);
			}

			virtual property unsigned short* Flags
			{
				unsigned short* get();
				void set(unsigned short* value);
			}

			virtual property unsigned short* Regs
			{
				unsigned short* get();
				void set(unsigned short* value);
			}

			virtual property unsigned short* Polys
			{
				unsigned short* get();
				void set(unsigned short* value);
			}

			virtual property unsigned short* Verts
			{
				unsigned short* get();
				void set(unsigned short* value);
			}
		};
	}

}