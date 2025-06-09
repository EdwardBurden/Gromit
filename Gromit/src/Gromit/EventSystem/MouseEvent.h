#pragma once
#include "EventBase.h"


class  MouseEvent : public EventBase
{
public:
	MouseEvent(char thing, EventType temp)
	{
		something = thing;
		eventType = temp;
	};
	~MouseEvent() {};
	char something;
};