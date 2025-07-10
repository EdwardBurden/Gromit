#pragma once
#include "Core.h"
#include "RenderAPIs/Context.h"

namespace Gromit {

	class GROMIT_API Window
	{
	public:
		int m_x, m_y;
		int m_height, m_width;
		bool m_close;
		virtual void UpdateWindow() = 0;
	protected:
		Context* m_context;
	};
}