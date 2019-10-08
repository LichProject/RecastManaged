#pragma once
#include "../Unmanaged/Recast/Recast.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class ContourSet
		{
			rcContourSet* _cset;
			bool _destructWithMe;
			bool _disposed;

		public:
			!ContourSet();

			ContourSet();

			ContourSet(rcContourSet* cset, bool* destructWithMe);

			~ContourSet();

			rcContourSet* GetPointer();

			virtual property int NConts { int get(); void set(int value); }

			virtual property rcContour* Conts { rcContour* get(); void set(rcContour* value); }
		};
	}

}