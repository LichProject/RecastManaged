#include "Span.h"

RecastManaged::Recast::Span::Span(rcSpan* s, bool* destructWithMe)
{
	this->_s = s;
	this->_destructWithMe = destructWithMe;
	this->_disposed = false;
}

RecastManaged::Recast::Span::!Span()
{
	if (!this->_disposed && this->_destructWithMe)
	{
		delete _s;
		_s = nullptr;
		this->_disposed = true;
	}
}

RecastManaged::Recast::Span::~Span()
{
	this->!Span();
}

rcSpan* RecastManaged::Recast::Span::GetPointer()
{
	return this->_s;
}

#pragma region HeightMin
void RecastManaged::Recast::Span::HeightMin::set(unsigned value)
{
	_s->smin = value;
}

unsigned RecastManaged::Recast::Span::HeightMin::get()
{
	return _s->smin;
}
#pragma endregion


#pragma region HeightMax
void RecastManaged::Recast::Span::HeightMax::set(unsigned value)
{
	_s->smax = value;
}

unsigned RecastManaged::Recast::Span::HeightMax::get()
{
	return _s->smax;
}
#pragma endregion


#pragma region Next
void RecastManaged::Recast::Span::Next::set(Span^ value)
{
	_s->next = value->GetPointer();
}

RecastManaged::Recast::Span^ RecastManaged::Recast::Span::Next::get()
{
	return gcnew Span(_s->next, false);
}
#pragma endregion
