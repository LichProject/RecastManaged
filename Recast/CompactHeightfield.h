#pragma once
#include "../Unmanaged/Recast/Recast.h"
#include "../Tools/Math/Vector3.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class CompactHeightfield
		{
			rcCompactHeightfield* _chf;
			bool _destructWithMe;
			bool _disposed;

		public:
			CompactHeightfield();

			CompactHeightfield(rcCompactHeightfield* chf, bool* destructWithMe);

			~CompactHeightfield();

			!CompactHeightfield();

			rcCompactHeightfield* GetPointer();

			virtual property unsigned char* Areas
			{
				unsigned char* get();
				void set(unsigned char* value);
			}

			virtual property Tools::Math::Vector3^ BMax
			{
				Tools::Math::Vector3^ get();
				void set(Tools::Math::Vector3^ value);
			}

			virtual property Tools::Math::Vector3^ BMin
			{
				Tools::Math::Vector3^ get();
				void set(Tools::Math::Vector3^ value);
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

			virtual property int Height
			{
				int get();
				void set(int value);
			}

			virtual property int WalkableClimb
			{
				int get();
				void set(int value);
			}

			virtual property int WalkableHeight
			{
				int get();
				void set(int value);
			}

			virtual property int Width
			{
				int get();
				void set(int value);
			}
		};
	}
}
