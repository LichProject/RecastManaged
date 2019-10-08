#pragma once
namespace RecastManaged
{
	namespace Detour
	{
		public enum class StatusDetailFlag : unsigned
		{
			Failure = 2147483648u,
			Success = 1073741824u,
			InProgress = 536870912u,
			WrongMagic = 1u,
			WrongVersion = 2u,
			OutOfMemory = 4u,
			InvalidParam = 8u,
			BufferTooSmall = 16u,
			OutOfNodes = 32u,
			PartialResult = 64u
		};
	}
}
