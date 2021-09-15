#ifndef MAINWINDOWVM_H
#define MAINWINDOWVM_H

#include <memory>
#include <QObject>

#include "screen_ratio_manager_vm.h"

class MainWindowVM : public QObject
{
	Q_OBJECT

	using ScreenRatioManagerVMPtr = std::shared_ptr<ScreenRatioManagerVM>;

	Q_PROPERTY(ScreenRatioManagerVM* screen_ratio_manager_vm READ get_screen_ratio_manager_vm_raw CONSTANT)

public:
	explicit MainWindowVM(QObject *parent = nullptr);
	ScreenRatioManagerVM* get_screen_ratio_manager_vm_raw() const noexcept;

private:
	ScreenRatioManagerVMPtr _screen_ratio_manager_vm;
};

#endif // MAINWINDOWVM_H
