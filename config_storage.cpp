#include "config_storage.h"

#include <QTextStream>

namespace
{
const QString default_config = "";
}

ConfigStorage::ConfigStorage()
	: _config_file("config.json")
{
	if (!_config_file.exists())
	{
		_config_file.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&_config_file);
		out << default_config;
		_config_file.close();
	}
}
