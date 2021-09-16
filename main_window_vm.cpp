#include "main_window_vm.h"

MainWindowVM::MainWindowVM(QObject *parent)
	: QObject(parent)
	, _screen_ratio_manager_vm(std::make_shared<ScreenRatioManagerVM>(this))
	, _tir_launcher(std::make_unique<TiRLauncher>())
{
	connect(this, &MainWindowVM::startGameRequested, _tir_launcher.get(), &TiRLauncher::start_game);
	connect(this, &MainWindowVM::gameFolderChoosed, _tir_launcher.get(), &TiRLauncher::set_path_to_game);
	connect(_screen_ratio_manager_vm.get(), &ScreenRatioManagerVM::currentRatioChanged, this, &MainWindowVM::set_screen_ratio_preset);
}

ScreenRatioManagerVM* MainWindowVM::get_screen_ratio_manager_vm_raw() const noexcept
{
	return _screen_ratio_manager_vm.get();
}

void MainWindowVM::set_screen_ratio_preset()
{
	_tir_launcher->set_screen_ratio_preset(_screen_ratio_manager_vm->get_current_ratio_preset());
}
