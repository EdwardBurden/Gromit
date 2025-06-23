#pragma once
#include "EventBase.h"
class   WindowsResizeEvent : public EventBase
{
public:
	WindowsResizeEvent(int _height,int _width): Height(_height), Width(_width) {}
	EVENT_TYPE_DEFINE(WindowsResizeEvent);
	int Height;
	int Width;
};
