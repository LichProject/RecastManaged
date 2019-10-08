#pragma once
#include "../Tools/Math/Vector3.h"
#include "../Unmanaged/Detour/DetourNavMesh.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class NavMeshParams
		{
			dtNavMeshParams* _nmp;
			bool _destructWithMe;
			bool _disposed;

		public:
			NavMeshParams(dtNavMeshParams* nmp, bool* destructWithMe);

			NavMeshParams(bool* destructWithMe);

			NavMeshParams();

			~NavMeshParams();

			!NavMeshParams();

			dtNavMeshParams* GetPointer();

			virtual property int MaxTiles
			{
				int get();
				void set(int value);
			}

			virtual property int MaxPolys
			{
				int get();
				void set(int value);
			}

			virtual property float TileWidth
			{
				float get();
				void set(float value);
			}

			virtual property float TileHeight
			{
				float get();
				void set(float value);
			}

			virtual property Tools::Math::Vector3^ Origin
			{
				Tools::Math::Vector3^ get();
				void set(Tools::Math::Vector3^ value);
			}
		};
	}
}
