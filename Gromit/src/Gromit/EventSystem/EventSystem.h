#pragma once
#include "EventBase.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "../Core.h"
#include "../pch.h"
#include "../IEngineService.h"
#include "../ServiceLocator.h"

namespace Gromit 
{
	class GROMIT_API EventSystem : public IEngineService
	{
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	
		EventSystem() 
		{
			std::cout << "EventSystem Constructor" << std::endl;
		}

		void OnStartUp() override;
		void OnShutDown() override;
		bool OnUpdate();
		
		template<typename T>
		void RegisterListener(void* listener, EventFn<T> func) {
			// todo have list of possible clases and do lookup?
			// todo, check the listener isnt already added

			std::function<bool(EventBase&)> wrapper = [func](EventBase& e) {
				//todo add check that event is actuallty of type T 
				// Only call the function if it's actually a T (e.g., WindowsEvent)
				T& actualEvent = static_cast<T&>(e);  // safely treat it as a T
				return func(actualEvent);             // call your real function

				return false; // Not the right type, don't call the function
				};
			EventType eventType = T::GetStaticEventType();
			m_registeredCallbacks[eventType][listener] = wrapper;
		}

		template<typename T>
		void UnregisterListener(void* listener) {
			auto eventType = T::GetStaticEventType();
			auto registered = m_registeredCallbacks[eventType];
			registered.erase(listener);
			if (registered.empty()) {
				m_registeredCallbacks.erase(eventType);
			}
		}

		template<typename T, typename... Args>
		void Trigger(Args&&... args) {
			T* e = new T(std::forward<Args>(args)...);
			m_frameTriggeredEvents.push_back(e);
		}


	private:
		void TriggerEvent(EventBase& event)
		{
			auto registered = m_registeredCallbacks[event.GetEventType()]; //todo check if any are avialable
			for (auto& it : registered) {
				bool handled = it.second(event);
			}
		}


		std::list<EventBase*> m_frameTriggeredEvents;
		using callbacks = std::unordered_map<void*, std::function<bool(EventBase&)>>; // may change, will need them orderer by priority
		std::unordered_map<EventType, callbacks> m_registeredCallbacks;
	};
}

#define REG_EVENT(ClassType, listener, func)                                \
    do {                                                                    \
        auto* sys = Gromit::ServiceLocator::GetService<Gromit::EventSystem>(); \
        assert(sys && "EventSystem not registered in ServiceLocator!");    \
        sys->RegisterListener<ClassType>(listener, [listener](ClassType& e) { return func(e); }); \
    } while (0)


//#define REG_EVENT(ClassType, listener, func)	Gromit::ServiceLocator::GetService<Gromit::EventSystem>()->RegisterListener<ClassType> \
(listener, [listener](ClassType& e) { return func(e); });

#define REG_EVENT_STATIC(ClassType, listener, func) Gromit::ServiceLocator::GetService<Gromit::EventSystem>()->RegisterListener<ClassType>(listener, func)
#define UREG_EVENT(ClassType, listener) Gromit::ServiceLocator::GetService<Gromit::EventSystem>()->UnregisterListener<ClassType>(listener)
#define TRIG_EVENT(ClassType, ...) Gromit::ServiceLocator::GetService<Gromit::EventSystem>()->Trigger<ClassType>(__VA_ARGS__)