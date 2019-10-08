#pragma once
#include "CompactSpan.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class Span
		{
			rcSpan* _s;
			bool _destructWithMe;
			bool _disposed;

		public:
            Span(rcSpan* s, bool* destructWithMe);

			!Span();

			~Span();

			rcSpan* GetPointer();

			virtual property Span^ Next
			{
				Span^ get();
				void set(Span^ value);
			}

			virtual property unsigned HeightMax
			{
				unsigned int get();
				void set(unsigned value);
			}

			virtual property unsigned HeightMin
			{
				unsigned get();
				void set(unsigned value);
			}
		};
	}
}