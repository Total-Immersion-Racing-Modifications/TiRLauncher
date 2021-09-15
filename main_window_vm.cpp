#include "main_window_vm.h"

MainWindowVM::MainWindowVM(QObject *parent)
	: QObject(parent)
	, _screen_ratio_manager_vm(std::make_shared<ScreenRatioManagerVM>(this))
{
}

ScreenRatioManagerVM* MainWindowVM::get_screen_ratio_manager_vm_raw() const noexcept
{
	return _screen_ratio_manager_vm.get();
}
