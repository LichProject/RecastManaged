#pragma once
#include "CompactHeightfield.h"

namespace RecastManaged
{
	namespace Recast
	{
		public ref class HeightfieldLayerSet
		{
			rcHeightfieldLayerSet* _lset;
			bool _destructWithMe;
			bool _disposed;

		public:
			HeightfieldLayerSet();

			HeightfieldLayerSet(rcHeightfieldLayerSet* lset, bool* destructWithMe);

			!HeightfieldLayerSet();

			~HeightfieldLayerSet();

			rcHeightfieldLayerSet* GetPointer();

			virtual property int NLayers
			{
				int get()
				{
					return _lset->nlayers;
				}
			}
		};
	}
}
