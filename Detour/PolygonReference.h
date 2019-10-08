#pragma once

namespace RecastManaged
{
	namespace Detour
	{
		public ref struct PolygonReference
		{
			PolygonReference(unsigned id);

			System::String^ ToString() override;

			unsigned Id;
		};
	}
}
