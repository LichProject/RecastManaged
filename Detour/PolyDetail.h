#pragma once
#include "Poly.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class PolyDetail
		{
			dtPolyDetail* _pd;
			bool _destructWithMe;
			bool _disposed;

		public:

			PolyDetail(dtPolyDetail* pd, bool* destructWithMe);

			PolyDetail();

			~PolyDetail();

			!PolyDetail();

			dtPolyDetail* GetPointer()
			{
				return _pd;
			}

			virtual property unsigned VertBase
			{
				unsigned get()
				{
					return _pd->vertBase;
				}
				void set(unsigned value)
				{
					_pd->vertBase = value;
				}
			}

			virtual property unsigned char VertCount
			{
				unsigned char get()
				{
					return _pd->vertCount;
				}
				void set(unsigned char value)
				{
					_pd->vertCount = value;
				}
			}

			virtual property unsigned TriBase
			{
				unsigned get()
				{
					return _pd->triBase;
				}
				void set(unsigned value)
				{
					_pd->triBase = value;
				}
			}

			virtual property unsigned char TriCount
			{
				unsigned char get()
				{
					return _pd->triCount;
				}
				void set(unsigned char value)
				{
					_pd->triCount = value;
				}
			}
		};
	}
}
