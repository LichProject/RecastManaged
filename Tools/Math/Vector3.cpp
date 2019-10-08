#include "Vector3.h"
using namespace System::Runtime::InteropServices;

bool RecastManaged::Tools::Math::Vector3::Equals(Vector3^ other)
{
	return
		double(X) == double(other->X) &&
		double(Y) == double(other->Y) &&
		double(Z) == double(other->Z);
}

bool RecastManaged::Tools::Math::Vector3::Equals(Object^ obj)
{
	if (ReferenceEquals(nullptr, obj))
	{
		return false;
	}

	try
	{
		return Equals(dynamic_cast<Vector3^>(obj));
	}
	catch (System::InvalidCastException^)
	{
	}

	return false;
}

int RecastManaged::Tools::Math::Vector3::GetHashCode()
{
	const auto xHashCode = X.GetHashCode() * 397;
	const auto yHashCode = Y.GetHashCode() * 397;
	return Z.GetHashCode() ^ yHashCode ^ xHashCode;
}

RecastManaged::Tools::Math::Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

float RecastManaged::Tools::Math::Vector3::LengthSqr()
{
	const double dY = Y;
	const double dX = X;
	const double dZ = Z;
	const auto dXdY = float(dX * dX);
	return float(float(dXdY + dY * dY) + dZ * dZ);
}

float RecastManaged::Tools::Math::Vector3::Length()
{
	return float(System::Math::Sqrt(LengthSqr()));
}

float RecastManaged::Tools::Math::Vector3::MagnitudeSqr::get()
{
	return LengthSqr();
}


float RecastManaged::Tools::Math::Vector3::Magnitude::get()
{
	return Length();
}

float RecastManaged::Tools::Math::Vector3::DistanceSqr(Vector3^ v)
{
	const auto num = float(double(X) - double(v->X));
	const auto num2 = float(double(Y) - double(v->Y));
	const auto num3 = float(double(Z) - double(v->Z));
	const double num4 = num2;
	const double num5 = num;
	const double num6 = num3;
	const double num7 = num5;
	const auto num8 = float(num7 * num7);
	const double num9 = num4;
	const auto num10 = float(num8 + num9 * num9);
	const double num11 = num6;
	return float(num10 + num11 * num11);
}

float RecastManaged::Tools::Math::Vector3::Distance(Vector3^ v)
{
	return System::Math::Sqrt(DistanceSqr(v));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Min(
	Vector3^ v1, Vector3^ v2)
{
	Vector3^ result = gcnew Vector3(0, 0, 0);
	Min(v1, v2, result);
	return result;
}

void RecastManaged::Tools::Math::Vector3::Min(Vector3^% v1,
                                              Vector3^% v2,
                                              [Out] Vector3^% result)
{
	result->X = System::Math::Min(v1->X, v2->X);
	result->Y = System::Math::Min(v1->Y, v2->Y);
	result->Z = System::Math::Min(v1->Z, v2->Z);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Max(
	Vector3^ v1, Vector3^ v2)
{
	Vector3^ result = gcnew Vector3(0, 0, 0);
	Max(v1, v2, result);
	return result;
}

void RecastManaged::Tools::Math::Vector3::Max(Vector3^% v1, Vector3^% v2,
                                              [Out] Vector3^% result)
{
	result->X = System::Math::Max(v1->X, v2->X);
	result->Y = System::Math::Max(v1->Y, v2->Y);
	result->Z = System::Math::Max(v1->Z, v2->Z);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Add(Vector3^ v)
{
	return gcnew Vector3(float(X + double(v->X)),
	                     float(Y + double(v->Y)),
	                     float(Z + double(v->Z)));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Divide(Vector3^ v)
{
	return gcnew Vector3(float(X / double(v->X)),
	                     float(Y / double(v->Y)),
	                     float(Z / double(v->Z)));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Divide(float divisor)
{
	return gcnew Vector3(float(X / double(divisor)),
	                     float(Y / double(divisor)),
	                     float(Z / double(divisor)));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Multiply(Vector3^ v)
{
	return gcnew Vector3(float(X * double(v->X)),
	                     float(Y * double(v->Y)),
	                     float(Z * double(v->Z)));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::Multiply(float factor)
{
	return gcnew Vector3(float(X * double(factor)),
	                     float(Y * double(factor)),
	                     float(Z * double(factor)));
}

void RecastManaged::Tools::Math::Vector3::Normalize()
{
	Vector3^ vector = Divide(Length());
	X = vector->X;
	Y = vector->Y;
	Z = vector->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator +(Vector3^ ls, Vector3^ rs)
{
	return ls->Add(rs);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator /(Vector3^ ls, Vector3^ rs)
{
	return ls->Divide(rs);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator /(Vector3^ ls, float rs)
{
	return ls->Divide(rs);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator *(Vector3^ ls, Vector3^ rs)
{
	return ls->Multiply(rs);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator *(Vector3^ ls, float rs)
{
	return ls->Multiply(rs);
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::operator -(Vector3^ ls, Vector3^ rs)
{
	return gcnew Vector3(float(ls->X - double(rs->X)),
	                     float(ls->Y - double(rs->Y)),
	                     float(ls->Z - double(rs->Z)));
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Tools::Math::Vector3::FromFloatPointer(float* pointer)
{
	return gcnew Vector3(pointer[0], pointer[1], pointer[2]);
}

array<float>^ RecastManaged::Tools::Math::Vector3::ToFloatArray()
{
	return gcnew array<float>(3){this->X, this->Y, this->Z};
}
