#pragma once
#include "StatusDetailFlag.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref struct Status
		{
			static Status();

			Status(unsigned status);

			System::String^ ToString() override;

			virtual property bool Failed
			{
				bool get();
			}

			virtual property bool Succeeded
			{
				bool get();
			}

			virtual property bool InProgress
			{
				bool get();
			}

			virtual property StatusDetailFlag Flags
			{
				StatusDetailFlag get();
			}

			bool HasFlag(StatusDetailFlag flag);

			unsigned Id;

			static Status^ Failure;

			static Status^ Success;
		};
	}
}