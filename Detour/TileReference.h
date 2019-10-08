#pragma once
namespace RecastManaged
{
	namespace Detour
	{
		public ref struct TileReference
		{
			TileReference(unsigned id);

			System::String^ ToString() override;

			unsigned Id;
		};
	}
}
