#pragma once
using namespace System;

namespace RecastManaged
{
	namespace Detour
	{
		[System::Flags]
		public enum class StraightPathFlags : unsigned char
		{
			None = 0,
			Start = 1,
			End = 2,
			OffmeshConnection = 4
		};
	}
}
