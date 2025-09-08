#pragma once
#include "EventSystem/EventType.h"

namespace Gromit {
	class EventBase {
	public:
		virtual EventType GetEventType() const = 0;
	};

#define EVENT_TYPE_DEFINE(eventType) \
static EventType GetStaticEventType() { return EventType::eventType; } \
virtual EventType GetEventType() const override  {return GetStaticEventType();}
}