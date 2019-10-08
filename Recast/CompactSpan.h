#pragma once
#include "CompactCell.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class CompactSpan
		{
			rcCompactSpan* _span;
			bool _destructWithMe;
			bool _disposed;

		public:
			!CompactSpan();

			CompactSpan(rcCompactSpan* span, bool* destructWithMe);

			~CompactSpan();

			rcCompactSpan* GetPointer();

			virtual property unsigned int Height
			{
				unsigned int get();
				void set(unsigned int value);
			}

			virtual property unsigned int Connections
			{
				unsigned int get();
				void set(unsigned int value);
			}

			virtual property unsigned short Reg
			{
				unsigned short get();
				void set(unsigned short value);
			}

			virtual property unsigned short Y
			{
				unsigned short get();
				void set(unsigned short value);
			}
		};
	}

}