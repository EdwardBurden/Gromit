#pragma once
#include "EventBase.h"


class  MouseEvent : public EventBase
{
public:
	//Abstract
};



class MouseClickEvent : public MouseEvent
{ 
public:
	MouseClickEvent(int _button) : button(_button) {}
	EVENT_TYPE_DEFINE(MouseClickEvent);
private:
	int button;
};

class MouseMoveEvent : public MouseEvent
{
public:
	MouseMoveEvent(int _x, int _y) : x(_x), y(_y){}
	EVENT_TYPE_DEFINE(MouseMoveEvent);
private:
	int x, y;
};

class MouseScrollEvent : public MouseEvent
{
public:
	MouseScrollEvent(int _scrollAmount) : scrollAmount(_scrollAmount) {}
	EVENT_TYPE_DEFINE(MouseScrollEvent);
private:
	int scrollAmount;
};