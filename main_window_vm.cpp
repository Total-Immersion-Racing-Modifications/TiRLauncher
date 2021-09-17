#include "main_window_vm.h"

namespace
{
const std::string path_to_game_folder_key("path_to_game_folder");
const std::string screen_ratio_key("screen_ratio");
}

MainWindowVM::MainWindowVM(QObject *parent)
	: QObject(parent)
	, _screen_ratio_manager_vm(std::make_shared<ScreenRatioManagerVM>(this))
	, _tir_launcher(std::make_unique<TiRLauncher>())
	, _config_storage(std::make_unique<ConfigStorage>())
{
	connect(this, &MainWindowVM::startGameRequested, _tir_launcher.get(), &TiRLauncher::start_game);
	connect(this, &MainWindowVM::gameFolderChoosed, _tir_launcher.get(), &TiRLauncher::set_path_to_game);
	connect(_screen_ratio_manager_vm.get(), &ScreenRatioManagerVM::currentRatioChanged, this, &MainWindowVM::set_screen_ratio_preset);
	// TODO: Move to ConfigStoreVM
	connect(this, &MainWindowVM::gameFolderChoosed, this, &MainWindowVM::save_game_folder);
	connect(_screen_ratio_manager_vm.get(), &ScreenRatioManagerVM::currentRatioChanged, this, &MainWindowVM::save_screen_ratio);
	const auto path_to_game_folder = _config_storage->get_string(path_to_game_folder_key);
	_tir_launcher->set_path_to_game(QString::fromStdString(path_to_game_folder));
	_screen_ratio_manager_vm->set_current_ratio(_config_storage->get_int(screen_ratio_key));
}

ScreenRatioManagerVM* MainWindowVM::get_screen_ratio_manager_vm_raw() const noexcept
{
	return _screen_ratio_manager_vm.get();
}

void MainWindowVM::set_screen_ratio_preset()
{
	_tir_launcher->set_screen_ratio_preset(_screen_ratio_manager_vm->get_current_ratio_preset());
}

void MainWindowVM::save_game_folder(QString path_to_game_folder)
{
	_config_storage->set_string(path_to_game_folder_key, _tir_launcher->get_path_to_game().toStdString());
}

void MainWindowVM::save_screen_ratio()
{
	_config_storage->set_int(screen_ratio_key, _screen_ratio_manager_vm->get_current_ratio());
}
