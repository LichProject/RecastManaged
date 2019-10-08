#pragma once
#include "../Unmanaged/Detour/DetourNavMeshQuery.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class QueryFilter
		{
			dtQueryFilter* _filter;
			bool _disposed = false;

		public:
			static initonly QueryFilter^ Default = gcnew QueryFilter();

			QueryFilter(unsigned short includeFlags, unsigned short excludeFlags);

			QueryFilter();

			~QueryFilter()
			{
				this->!QueryFilter();
			}

			!QueryFilter();

			dtQueryFilter* GetPointer()
			{
				return this->_filter;
			}

			virtual property unsigned short IncludeFlags
			{
				unsigned short get()
				{
					return _filter->getIncludeFlags();
				}

				void set(unsigned short value)
				{
					_filter->setIncludeFlags(value);
				}
			}

			virtual property unsigned short ExcludeFlags
			{
				unsigned short get()
				{
					return _filter->getExcludeFlags();
				}

				void set(unsigned short value)
				{
					_filter->setExcludeFlags(value);
				}
			}

			float GetAreaCost(unsigned char areaId);

			void SetAreaCost(unsigned char areaId, float cost);
		};
	}
}
