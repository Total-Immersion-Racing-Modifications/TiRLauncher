#include "main_window_vm.h"

MainWindowVM::MainWindowVM(QObject *parent)
	: QObject(parent)
	, _current_ratio(screen_ratio::ScreenRatioPresetType::Undefined)
	, _ratio_manager(std::make_unique<screen_ratio::ScreenRatioManager>())
{
	if (_ratio_manager == nullptr)
	{
		throw std::exception("Ratio Manager is null");
	}
}

void MainWindowVM::set_current_ratio(int new_ratio) noexcept
{
	_current_ratio = static_cast<screen_ratio::ScreenRatioPresetType>(new_ratio);
	emit currentRatioChanged();
}

int MainWindowVM::get_current_ratio() const noexcept
{
	return static_cast<int>(_current_ratio);
}
