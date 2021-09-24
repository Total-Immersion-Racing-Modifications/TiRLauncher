#ifndef MAINWINDOWVM_H
#define MAINWINDOWVM_H

#include <memory>
#include <QObject>

#include "screen_ratio_manager_vm.h"
#include "tir_launcher.h"
#include "config_storage_adapter.h"

class MainWindowVM : public QObject
{
	Q_OBJECT

	using ScreenRatioManagerVMPtr = std::shared_ptr<ScreenRatioManagerVM>;
	using TiRLauncherPtr = std::unique_ptr<TiRLauncher>;
	using ConfigStorageVMPtr = std::unique_ptr<ConfigStorageAdapter>;

	Q_PROPERTY(ScreenRatioManagerVM* screen_ratio_manager_vm READ get_screen_ratio_manager_vm_raw CONSTANT)

public:
	explicit MainWindowVM(QObject *parent = nullptr);
	ScreenRatioManagerVM* get_screen_ratio_manager_vm_raw() const noexcept;

signals:
	void startGameRequested();
	void gameFolderChoosed(QString path_to_game_folder);

private slots:
	void set_screen_ratio_preset() noexcept;
	void save_screen_ratio() noexcept;

private:
	ScreenRatioManagerVMPtr _screen_ratio_manager_vm;
	TiRLauncherPtr _tir_launcher;
	ConfigStorageVMPtr _config_storage_vm;
};

#endif // MAINWINDOWVM_H
