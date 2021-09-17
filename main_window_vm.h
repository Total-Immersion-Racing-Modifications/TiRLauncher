#ifndef MAINWINDOWVM_H
#define MAINWINDOWVM_H

#include <memory>
#include <QObject>

#include "screen_ratio_manager_vm.h"
#include "tir_launcher.h"
#include "config_storage.h"

class MainWindowVM : public QObject
{
	Q_OBJECT

	using ScreenRatioManagerVMPtr = std::shared_ptr<ScreenRatioManagerVM>;
	using TiRLauncherPtr = std::unique_ptr<TiRLauncher>;
	using ConfigStoragePtr = std::unique_ptr<ConfigStorage>;

	Q_PROPERTY(ScreenRatioManagerVM* screen_ratio_manager_vm READ get_screen_ratio_manager_vm_raw CONSTANT)

public:
	explicit MainWindowVM(QObject *parent = nullptr);
	ScreenRatioManagerVM* get_screen_ratio_manager_vm_raw() const noexcept;

signals:
	void startGameRequested();
	void gameFolderChoosed(QString path_to_game_folder);

private slots:
	void set_screen_ratio_preset();
	void save_game_folder(QString path_to_game_folder);
	void save_screen_ratio();

private:
	ScreenRatioManagerVMPtr _screen_ratio_manager_vm;
	TiRLauncherPtr _tir_launcher;
	ConfigStoragePtr _config_storage;
};

#endif // MAINWINDOWVM_H
