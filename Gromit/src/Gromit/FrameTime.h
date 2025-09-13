#pragma once 

namespace Gromit {

	class FrameTime
	{
	public:
		static float DeltaTime;
		static void SetDelta();

	private:
		static float m_lastFrameTime;
	};
}