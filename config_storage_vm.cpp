#include "config_storage_vm.h"

namespace
{
const std::string path_to_game_folder_key("path_to_game_folder");
const std::string screen_ratio_key("screen_ratio");
}

ConfigStorageVM::ConfigStorageVM()
	: _config_storage(std::make_unique<ConfigStorage>())
{

}

QString ConfigStorageVM::get_game_foler() const noexcept
{
	return QString::fromStdString(_config_storage->get_string(path_to_game_folder_key));
}

int ConfigStorageVM::get_screen_ratio() const noexcept
{
	return _config_storage->get_int(screen_ratio_key);
}

void ConfigStorageVM::save_game_folder(QString path_to_game_folder) noexcept
{
	_config_storage->set_string(path_to_game_folder_key, path_to_game_folder.toStdString());
}

void ConfigStorageVM::save_screen_ratio(int screen_ratio_type) noexcept
{
	_config_storage->set_int(screen_ratio_key, screen_ratio_type);
}
