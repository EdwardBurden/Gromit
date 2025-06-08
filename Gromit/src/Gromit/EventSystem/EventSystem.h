#include "EventType.h"
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

namespace Gromit {

	class Event {
	public:
		enum EventType eventType;
		//virtual EventType GetEventType() const = 0;
	};

	class WindowsEvent : public Event
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


	class  MouseEvent : public Event
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



	class EventSystem {
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		EventSystem() {}
		~EventSystem() {}


		template<typename T>
		void RegisterListener(EventType eventType, void* listener, EventFn<T> func) {
			// todo, check the listener isnt already added

			std::function<bool(Event&)> wrapper = [func](Event& e) {
				//todo add check that event is actuallty of type T 
				// Only call the function if it's actually a T (e.g., WindowsEvent)
				T& actualEvent = static_cast<T&>(e);  // safely treat it as a T
				return func(actualEvent);             // call your real function

				return false; // Not the right type, don't call the function
				};
			m_registeredCallbacks[eventType][listener] = wrapper;
		}

		void UnregisterListener(EventType eventType, void* listener) {
			auto registered = m_registeredCallbacks[eventType];
			registered.erase(listener);
			if (registered.empty()) {
				m_registeredCallbacks.erase(eventType);
			}
		}

		/*void Trigger(Event* event) {
			m_frameTriggeredEvents.push_back(event);
		}*/

		template<typename T, typename... Args>
		void Trigger(Args&&... args) {
			T* e = new T(std::forward<Args>(args)...);
			m_frameTriggeredEvents.push_back(e);
		}


		void PerFrame() {
			while (!m_frameTriggeredEvents.empty())
			{
				auto event = m_frameTriggeredEvents.back();
				TriggerEvent(*event);
				m_frameTriggeredEvents.pop_back();
				delete event;
			}
		}

	private:

		void TriggerEvent(Event& event) {
			auto registered = m_registeredCallbacks[event.eventType]; //todo check if any are avialable
			for (auto& it : registered) {
				bool handled = it.second(event);
			}
		}
		std::vector<Event*> m_frameTriggeredEvents;


		using callbacks = std::unordered_map<void*, std::function<bool(Event&)>>; // may change, will need them orderer by priority
		std::unordered_map<EventType, callbacks> m_registeredCallbacks;
	};
}