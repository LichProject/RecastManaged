#pragma once
using namespace System;

namespace RecastManaged
{
	namespace Detour
	{
		[System::Flags]
		public enum class DirectionFlags
		{
			StartToEnd = 0,
			Bidirectional = 1
		};
	}
}
