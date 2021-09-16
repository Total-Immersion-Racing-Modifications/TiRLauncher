#ifndef TIRLAUNCHER_H
#define TIRLAUNCHER_H

#include <memory>
#include <QProcess>
#include <windows.h>

#include "screen_ratio_preset_type.h"

class TiRLauncher : public QObject
{
	Q_OBJECT

	using ScreenRatioPreset = std::pair<int, int>;
	using QProcessPtr = std::unique_ptr<QProcess>;

public:
	TiRLauncher();

public slots:
	void set_screen_ratio_preset(const ScreenRatioPreset& preset) noexcept;
	void start_game();

private:
	DWORD get_pid_by_process_name(const wchar_t *lpszProcessName);

private:
	const QString _tir_proc_name;
	ScreenRatioPreset _screen_ratio_preset;
	QProcessPtr _process;
};

#endif // TIRLAUNCHER_H
