#include "config_storage.h"

#include <fstream>

namespace
{
const std::string default_config("{\"path_to_game_folder\":\"\",\"screen_ratio\":4}");
}

ConfigStorage::ConfigStorage()
	: _config_file("config.json")
{
	if (!config_file_exist())
	{
		std::ofstream out(_config_file);
		if (out.is_open())
		{
			out << default_config;
			out.close();
		}
	}
	std::ifstream input(_config_file);
	if (input.is_open())
	{
		input >> j;
		input.close();
	}
}

ConfigStorage::~ConfigStorage()
{
	std::ofstream out(_config_file);
	if (out.is_open())
	{
		out << j;
		out.close();
	}
}

std::string ConfigStorage::get_string(const std::string& key) const noexcept
{
	return j[key].get<std::string>();
}

int ConfigStorage::get_int(const std::string &key) const noexcept
{
	return j[key].get<int>();
}

void ConfigStorage::set_string(const std::string &key, const std::string &value) noexcept
{
	j[key] = value;
}

void ConfigStorage::set_int(const std::string &key, const int value) noexcept
{
	j[key] = value;
}
