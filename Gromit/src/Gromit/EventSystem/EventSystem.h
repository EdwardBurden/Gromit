#pragma once
#include "EventBase.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "../Core.h"
#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

namespace Gromit {
	class GROMIT_API EventSystem {
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	
		EventSystem() {};
		~EventSystem() {};
		inline static EventSystem& Get() {
			static EventSystem instance;
			return instance;
		}
		
		template<typename T>
		void RegisterListener(EventType eventType, void* listener, EventFn<T> func) {
			// todo, check the listener isnt already added

			std::function<bool(EventBase&)> wrapper = [func](EventBase& e) {
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
		EventSystem(const EventSystem&) = delete;     // no copy
		EventSystem& operator=(const EventSystem&) = delete; // no assignment

		void TriggerEvent(EventBase& event) {
			auto registered = m_registeredCallbacks[event.eventType]; //todo check if any are avialable
			for (auto& it : registered) {
				bool handled = it.second(event);
			}
		}
		std::vector<EventBase*> m_frameTriggeredEvents;


		using callbacks = std::unordered_map<void*, std::function<bool(EventBase&)>>; // may change, will need them orderer by priority
		std::unordered_map<EventType, callbacks> m_registeredCallbacks;
	};
}

#define REG_EVENT(ClassType, eventType, listener, func) Gromit::EventSystem::Get().RegisterListener<ClassType>(eventType, listener, func)
//#define UREG_EVENT(eventType, listener) Gromit::EventSystem::s_eventSystem->UnregisterListener(eventType, listener)
#define TRIG_EVENT(ClassType, ...) Gromit::EventSystem::Get().Trigger<ClassType>(__VA_ARGS__)