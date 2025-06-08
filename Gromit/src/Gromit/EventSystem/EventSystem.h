#include "EventType.h"
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

namespace Gromit {

	class Event {
	public:
		enum EventType eventType;

	};



	class EventSystem {
	public:
		using EventFn = std::function<bool(Event&)>;
		EventSystem() {}
		~EventSystem() {}


		//template<typename T>


		void RegisterListener(EventType eventType, void* listener, EventFn callback) {
			// todo, check the listener isnt already added
			m_registeredCallbacks[eventType][listener] = callback;
		}

		void UnregisterListener(EventType eventType, void* listener) {
			auto registered = m_registeredCallbacks[eventType];
			registered.erase(listener);
			if (registered.empty()) {
				m_registeredCallbacks.erase(eventType);
			}
		}

		void Trigger(Event& event) {
			m_frameTriggeredEvents.push_back(event);
		}

		void PerFrame() {
			while (!m_frameTriggeredEvents.empty())
			{
				TriggerEvent(m_frameTriggeredEvents.back());
				m_frameTriggeredEvents.pop_back();
			}
		}

	private:

		void TriggerEvent(Event& event) {
			auto registered = m_registeredCallbacks[event.eventType]; //todo check if any are avialable
			for (auto& it : registered) {
				bool handled = it.second(event);
			}
		}
		std::vector<Event> m_frameTriggeredEvents;


		using callbacks = std::unordered_map<void*, std::function<bool(Event&)>>; // may change, will need them orderer by priority
		std::unordered_map<EventType, callbacks> m_registeredCallbacks;
	};
}