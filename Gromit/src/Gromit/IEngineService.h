#pragma once
namespace Gromit
{
	class IEngineService
	{
	public:
		virtual ~IEngineService() {};
		virtual void OnStartUp() = 0;
		virtual void OnShutDown() = 0;

	protected:

	};
}