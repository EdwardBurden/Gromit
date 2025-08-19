#pragma once

#include "IEngineService.h"
#include <map>
#include <typeinfo> // Required for typeid
#include <typeindex>

namespace Gromit
{
	class GROMIT_API ServiceLocator
	{
	public:
		template<typename T>
		static void RegisterService()
		{
			std::type_index index = typeid(T);
			if (m_registry.contains(index))
				return;

			auto ptr = new T();
			m_registry[index] = ptr;
			m_registerOrder.push_back(ptr);
		}

		template<typename T>
		static T* GetService()
		{
			auto it = m_registry.find(typeid(T));
			if (it == m_registry.end())
				return nullptr;

			return static_cast<T*>(it->second);
		}

		static void StartUp()
		{
			for (auto service : m_registerOrder)
			{
				service->OnStartUp();
			}
		}

		static void ShutDown()
		{
			for (auto it = m_registerOrder.rbegin(); it != m_registerOrder.rend(); ++it) //todo have second iterator list instead
			{
				(*it)->OnShutDown();
			}
		}

	private:
		static inline std::map<std::type_index, IEngineService*> m_registry; //made and added to
		static inline std::vector<IEngineService*> m_registerOrder;
	};
}