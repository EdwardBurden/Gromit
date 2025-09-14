#pragma once
#include <json.hpp>

namespace Gromit 
{
	struct MetaData
	{
	public:
		int m_guid;
		std::string m_name;
		std::string m_path;

		MetaData(int guid, nlohmann::json data)
		{
			data.at("guid").get_to(m_guid);
			data.at("name").get_to(m_name);
			data.at("path").get_to(m_path);
		}
	};
}