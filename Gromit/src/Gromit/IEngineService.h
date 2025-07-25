#pragma once
namespace Gromit
{
	class IEngineService
	{

	public:
		virtual void OnStartUp() = 0;
		virtual void OnShutDown() = 0;
		virtual bool OnUpdate() = 0; //true is blocked, false is not

	protected:

	};
}