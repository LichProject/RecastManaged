#include "OffMeshConnection.h"

RecastManaged::Detour::OffMeshConnection::OffMeshConnection(dtOffMeshConnection* con, bool* destructWithMe)
{
	this->_con = con;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::OffMeshConnection::OffMeshConnection(bool* destructWithMe)
{
	this->_con = new dtOffMeshConnection();
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Detour::OffMeshConnection::OffMeshConnection()
{
	this->_con = new dtOffMeshConnection();
	this->_destructWithMe = true;
	this->_disposed = false;
}

RecastManaged::Detour::OffMeshConnection::~OffMeshConnection()
{
	this->!OffMeshConnection();
}

RecastManaged::Detour::OffMeshConnection::!OffMeshConnection()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _con;
		_con = nullptr;
		
		this->_disposed = true;
	}
}

dtOffMeshConnection* RecastManaged::Detour::OffMeshConnection::GetPointer()
{
	return this->_con;
}

#pragma region Side
void RecastManaged::Detour::OffMeshConnection::Side::set(unsigned char value)
{
	_con->side = value;
}

unsigned char RecastManaged::Detour::OffMeshConnection::Side::get()
{
	return _con->side;
}
#pragma endregion


#pragma region Flags
void RecastManaged::Detour::OffMeshConnection::Flags::set(DirectionFlags value)
{
	_con->flags = static_cast<unsigned char>(value);
}

RecastManaged::Detour::DirectionFlags RecastManaged::Detour::OffMeshConnection::Flags::get()
{
	return DirectionFlags(_con->flags);
}
#pragma endregion


#pragma region PolyIndex
void RecastManaged::Detour::OffMeshConnection::PolyIndex::set(unsigned short value)
{
	_con->poly = value;
}

unsigned short RecastManaged::Detour::OffMeshConnection::PolyIndex::get()
{
	return _con->poly;
}
#pragma endregion


#pragma region Radius
void RecastManaged::Detour::OffMeshConnection::Radius::set(float value)
{
	_con->rad = value;
}

float RecastManaged::Detour::OffMeshConnection::Radius::get()
{
	return _con->rad;
}
#pragma endregion


#pragma region End
void RecastManaged::Detour::OffMeshConnection::End::set(Tools::Math::Vector3^ value)
{
	_con->pos[3] = value->X;
	_con->pos[4] = value->Y;
	_con->pos[5] = value->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Detour::OffMeshConnection::End::get()
{
	auto const pos = _con->pos;
	return gcnew Tools::Math::Vector3(pos[3], pos[4], pos[5]);
}
#pragma endregion


#pragma region Start
void RecastManaged::Detour::OffMeshConnection::Start::set(Tools::Math::Vector3^ value)
{
	_con->pos[0] = value->X;
	_con->pos[1] = value->Y;
	_con->pos[2] = value->Z;
}

RecastManaged::Tools::Math::Vector3^ RecastManaged::Detour::OffMeshConnection::Start::get()
{
	return Tools::Math::Vector3::FromFloatPointer(_con->pos);
}
#pragma endregion
