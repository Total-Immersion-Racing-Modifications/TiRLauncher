#ifndef MAINWINDOWVM_H
#define MAINWINDOWVM_H

#include <memory>
#include <QObject>

#include "screen_ratio_preset_type.h"
#include "screen_ratio_manager.h"

class MainWindowVM : public QObject
{
	Q_OBJECT

	using ScreenRatioManagerPtr = std::unique_ptr<screen_ratio::ScreenRatioManager>;

	Q_PROPERTY(int current_ratio READ get_current_ratio WRITE set_current_ratio NOTIFY currentRatioChanged);
public:
	explicit MainWindowVM(QObject *parent = nullptr);

signals:
	void currentRatioChanged();

private:
	void set_current_ratio(int new_ratio) noexcept;
	int get_current_ratio() const noexcept;

private:
	screen_ratio::ScreenRatioPresetType _current_ratio;
	ScreenRatioManagerPtr _ratio_manager;
};

#endif // MAINWINDOWVM_H
