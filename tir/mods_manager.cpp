#include "mods_manager.h"

#include <filesystem>
#include <QDir>
#include <QDebug>

namespace
{
const QString mods_folder_path("%1/mods");
const std::string mod_file_type(".dll");
const char inactive_mod_flag = '_';
}

namespace tir
{

ModsManager::ModsManager()
	: _mods_folder_path(mods_folder_path.arg(QDir::currentPath()))
{
	make_mods_files();
}

ModsManager::ModsFiles ModsManager::get_mods_folder() const noexcept
{
	return _mods_files;
}

void ModsManager::make_mods_files() noexcept
{
	try
	{
		_mods_files.clear();
		for (const auto& entry : std::filesystem::directory_iterator(_mods_folder_path.toStdString()))
		{
			if (const auto& file_path = entry.path().string(); is_mod(file_path))
			{
				_mods_files.emplace_back(entry.path().string());
			}
		}
	}
	catch (std::exception& e)
	{
		qDebug() << "Failed to get mods list: " << e.what();
	}
}

bool ModsManager::is_mod(const std::string &file_path)
{
	return file_path.substr(file_path.length() - mod_file_type.length(), mod_file_type.length()) == mod_file_type;
}

} // namespace tir
