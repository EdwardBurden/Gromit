#pragma once

namespace Gromit 
{
	class Window
	{
	public:
		int m_x, m_y;
		int m_height, m_width;
		bool m_close;
		virtual void Activate() = 0;
		virtual void PreUpdate() = 0;
		virtual void PostUpdate() = 0;
	protected:
	};
}