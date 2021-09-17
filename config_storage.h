#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include "json.hpp"

#include <sys/stat.h>

class ConfigStorage
{
public:
	explicit ConfigStorage();
	~ConfigStorage();

	std::string get_string(const std::string& key) const noexcept;
	int get_int(const std::string& key) const noexcept;

	void set_string(const std::string& key, const std::string& value) noexcept;
	void set_int(const std::string& key, const int value) noexcept;

private:
	inline bool config_file_exist() noexcept
	{
		struct stat buffer;
		return stat(_config_file.c_str(), &buffer) == 0;
	}

private:
	std::string _config_file;
	nlohmann::json j;
};

#endif // CONFIGSTORAGE_H
