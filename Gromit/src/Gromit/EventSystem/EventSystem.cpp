#include "EventSystem.h"

namespace Gromit
{

	void EventSystem::OnStartUp()
	{
	
	}

	void EventSystem::OnShutDown()
	{
	
	}

	bool EventSystem::OnUpdate()
	{
		while (!m_frameTriggeredEvents.empty())
		{
			auto event = m_frameTriggeredEvents.front();
			TriggerEvent(*event);
			m_frameTriggeredEvents.pop_front();
			delete event;
		}
		return false;
	}
}