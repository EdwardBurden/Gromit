#pragma once
namespace Gromit
{
	class IEngineService
	{
	public:
		virtual void OnStartUp() = 0;
		virtual void OnShutDown() = 0;


         IEngineService() = default;

        //Virtual destructor
        // Ensures proper cleanup when deleting derived services through a base pointer.
        virtual ~IEngineService() = default;

        //Delete copy constructor
        // Prevents creating accidental duplicates of engine services.
        IEngineService(const IEngineService&) = delete;

        //Delete copy assignment operator
        // Prevents overwriting one service’s state with another.
        IEngineService& operator=(const IEngineService&) = delete;

        //Default move constructor
        // Allows moving the service if needed (e.g., storing in a container).
        IEngineService(IEngineService&&) noexcept = default;

        //Default move assignment operator
        // Allows moving service instances between owners (rarely used, but safe).
        IEngineService& operator=(IEngineService&&) noexcept = default;
	protected:

	};
}