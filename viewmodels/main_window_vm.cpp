#include "main_window_vm.h"

MainWindowVM::MainWindowVM(QObject *parent)
	: QObject(parent)
	, _screen_ratio_manager_vm(std::make_shared<ScreenRatioManagerVM>(this))
	, _tir_launcher(std::make_unique<tir::TiRLauncher>())
	, _config_storage_vm(std::make_unique<config_storage::ConfigStorageAdapter>())
{
	connect(this, &MainWindowVM::startGameRequested, _tir_launcher.get(), &tir::TiRLauncher::start_game);
	connect(this, &MainWindowVM::gameFolderChoosed, _tir_launcher.get(), &tir::TiRLauncher::set_path_to_game);
	connect(_screen_ratio_manager_vm.get(), &ScreenRatioManagerVM::currentRatioChanged, this, &MainWindowVM::set_screen_ratio_preset);
	connect(this, &MainWindowVM::gameFolderChoosed, _config_storage_vm.get(), &config_storage::ConfigStorageAdapter::save_game_folder);
	connect(_screen_ratio_manager_vm.get(), &ScreenRatioManagerVM::currentRatioChanged, this, &MainWindowVM::save_screen_ratio);
	_tir_launcher->set_path_to_game(_config_storage_vm->get_game_foler());
	_screen_ratio_manager_vm->set_current_ratio(_config_storage_vm->get_screen_ratio());
}

ScreenRatioManagerVM* MainWindowVM::get_screen_ratio_manager_vm_raw() const noexcept
{
	return _screen_ratio_manager_vm.get();
}

void MainWindowVM::set_screen_ratio_preset()  noexcept
{
	_tir_launcher->set_screen_ratio_preset(_screen_ratio_manager_vm->get_current_ratio_preset());
}

void MainWindowVM::save_screen_ratio() noexcept
{
	_config_storage_vm->save_screen_ratio(_screen_ratio_manager_vm->get_current_ratio());
}
