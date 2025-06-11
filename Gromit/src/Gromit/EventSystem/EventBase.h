#pragma once
#include "EventType.h"

class  EventBase {
public:
	virtual EventType GetEventType() const =0;
	//static EventType GetStaticEventType();
};

#define EVENT_TYPE_DEFINE(eventType) \
static EventType GetStaticEventType() { return EventType::eventType; } \
virtual EventType GetEventType() const override  {return GetStaticEventType();}