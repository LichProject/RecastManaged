#include "Status.h"
#include "StatusDetailFlag.h"

static RecastManaged::Detour::Status::Status()
{
	Failure = gcnew Status(unsigned(StatusDetailFlag::Failure));
	Success = gcnew Status(unsigned(StatusDetailFlag::Success));
}

RecastManaged::Detour::Status::Status(unsigned status)
{
	this->Id = status;
}

System::String^ RecastManaged::Detour::Status::ToString()
{
	return StatusDetailFlag(this->Flags).ToString();
}

bool RecastManaged::Detour::Status::HasFlag(StatusDetailFlag flag)
{
	return (this->Id & unsigned(flag)) != 0u;
}

RecastManaged::Detour::StatusDetailFlag RecastManaged::Detour::Status::Flags::get()
{
	return StatusDetailFlag(Id);
}

bool RecastManaged::Detour::Status::InProgress::get()
{
	return HasFlag(StatusDetailFlag::InProgress);
}

bool RecastManaged::Detour::Status::Succeeded::get()
{
	return HasFlag(StatusDetailFlag::Success);
}

bool RecastManaged::Detour::Status::Failed::get()
{
	return HasFlag(StatusDetailFlag::Failure);
}
