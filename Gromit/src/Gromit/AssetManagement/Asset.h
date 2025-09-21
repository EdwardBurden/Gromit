#pragma once;

namespace Gromit
{
	struct Asset 
	{
		Asset(int guid) : m_guid(guid)
		{
		
		}


		int GetGuid() const { return m_guid; }
	private:
		int m_guid;
	};
}