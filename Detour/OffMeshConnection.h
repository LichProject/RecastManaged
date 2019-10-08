#pragma once
#include "../Unmanaged/Detour/DetourNavMesh.h"
#include "DirectionFlags.h"
#include "../Tools/Math/Vector3.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class OffMeshConnection
		{
			dtOffMeshConnection* _con;
			bool _destructWithMe;
			bool _disposed;

		public:
			OffMeshConnection(dtOffMeshConnection* con, bool* destructWithMe);

			OffMeshConnection(bool* destructWithMe);

			OffMeshConnection();

			~OffMeshConnection();

			!OffMeshConnection();

			dtOffMeshConnection* GetPointer();

			virtual property Tools::Math::Vector3^ Start
			{
				Tools::Math::Vector3^ get();
				void set(Tools::Math::Vector3^ value);
			}

			virtual property Tools::Math::Vector3^ End
			{
				Tools::Math::Vector3^ get();
				void set(Tools::Math::Vector3^ value);
			}

			virtual property float Radius
			{
				float get();
				void set(float value);
			}

			virtual property unsigned short PolyIndex
			{
				unsigned short get();
				void set(unsigned short value);
			}

			virtual property DirectionFlags Flags
			{
				DirectionFlags get();
				void set(DirectionFlags value);
			}

			virtual property unsigned char Side
			{
				unsigned char get();
				void set(unsigned char value);
			}
		};
	}
}
