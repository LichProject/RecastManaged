#pragma once
#include "../Unmanaged/Recast/Recast.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class CompactCell
		{
			rcCompactCell* _cell;
			bool _destructWithMe;
			bool _disposed;

		public:
			CompactCell(rcCompactCell* cell, bool* destructWithMe);

			~CompactCell();

			!CompactCell();

			rcCompactCell* GetPointer();

			virtual property unsigned int Index
			{
				unsigned int get();
				void set(unsigned int value);
			}

			virtual property unsigned int Count
			{
				unsigned int get();
				void set(unsigned int value);
			}
		};
	}

}