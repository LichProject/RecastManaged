#pragma once
using namespace System::Runtime::InteropServices;

namespace RecastManaged
{
	namespace Tools
	{
		namespace Math
		{
			public ref class Vector3
			{
			public:
				bool Equals(Vector3^ other);

				bool Equals(Object^ obj) override;

				int GetHashCode() override;

				Vector3(float x, float y, float z);

				float LengthSqr();

				float Length();

				virtual property float MagnitudeSqr
				{
					float get();
				}

				virtual property float Magnitude
				{
					float get();
				}

				float DistanceSqr(Vector3^ v);

				float Distance(Vector3^ v);

				static Vector3^ Min(Vector3^ v1, Vector3^ v2);

				static void Min(Vector3^% v1, Vector3^% v2, [Out] Vector3^% result);

				static Vector3^ Max(Vector3^ v1, Vector3^ v2);

				static void Max(Vector3^% v1, Vector3^% v2, [Out] Vector3^% result);

				Vector3^ Add(Vector3^ v);

				Vector3^ Divide(Vector3^ v);

				Vector3^ Divide(float divisor);

				Vector3^ Multiply(Vector3^ v);

				Vector3^ Multiply(float factor);

				void Normalize();

				static Vector3^ operator +(Vector3^ ls, Vector3^ rs);

				static Vector3^ operator /(Vector3^ ls, Vector3^ rs);

				static Vector3^ operator /(Vector3^ ls, float rs);

				static Vector3^ operator *(Vector3^ ls, Vector3^ rs);

				static Vector3^ operator *(Vector3^ ls, float rs);

				static Vector3^ operator -(Vector3^ ls, Vector3^ rs);

				static Vector3^ FromFloatPointer(float* pointer);

				array<float>^ ToFloatArray();

				float X;
				float Y;
				float Z;
			};
		}
	}
}
