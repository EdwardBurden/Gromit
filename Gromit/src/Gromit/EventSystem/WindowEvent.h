#pragma once
#include "EventBase.h"
class   WindowsEvent : public EventBase
{
public:
	WindowsEvent(int thing, EventType temp)
	{
		something = thing;
		eventType = temp;
	}
	~WindowsEvent() {}
	int something;
};