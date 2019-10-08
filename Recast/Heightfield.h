#pragma once
#include "Span.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class Heightfield
		{
			rcHeightfield* _hf;
			bool _destructWithMe;
			bool _disposed;

		public:
			!Heightfield();

			Heightfield();

			Heightfield(rcHeightfield* hf, bool* destructWithMe);

			~Heightfield();

			rcHeightfield* GetPointer();

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

			virtual property array<float>^ BoundsMax
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			virtual property array<float>^ BoundsMin
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			virtual property int Height
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