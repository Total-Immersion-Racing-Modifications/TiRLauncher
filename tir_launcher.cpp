#include "tir_launcher.h"

#include <QDebug>
#include <string>
#include <QUrl>
#include <QDesktopServices>
#include <tlhelp32.h>

TiRLauncher::TiRLauncher()
	: _tir_proc_name("tir.exe")
	, _process(std::make_unique<QProcess>())
	, _first_address(0x51a3c8 + 0x4)
	, _second_address(0x51a408 + 0x4)
	, _third_address(0x51a3ec)
{

}

void TiRLauncher::set_screen_ratio_preset(const ScreenRatioPreset &preset) noexcept
{
	_screen_ratio_preset = preset;
}

void TiRLauncher::set_path_to_game(const QString& path_to_game) noexcept
{
	_path_to_game = path_to_game;
}

void TiRLauncher::start_game()
{
	try
	{
		if (_path_to_game.length() == 0)
		{
			throw std::exception("You didn't choose game folder!");
		}
		QString path_to_exe(_path_to_game + "/" + _tir_proc_name);
		QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(path_to_exe)));
		const auto proc_pid = get_pid_by_process_name(_tir_proc_name.toStdWString().c_str());
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_pid);
		if (hProcess == NULL)
		{
			CloseHandle(hProcess);
			throw std::exception("Can't open the target process!");
		}
		WriteProcessMemory(hProcess, (LPVOID)_first_address, &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)_second_address, &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)_third_address, &_screen_ratio_preset.second, sizeof(_screen_ratio_preset.second), 0);
	}
	catch (std::exception& e)
	{
		qDebug() << e.what();
	}
}

DWORD TiRLauncher::get_pid_by_process_name(const wchar_t *lpszProcessName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 pe32 = { 0 };

	pe32.dwSize = sizeof(PROCESSENTRY32);

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		throw std::exception("Can't create the snapshot!");
	}

	if (Process32First(hSnapshot, &pe32))
	{
		do
		{
			if (wcscmp(pe32.szExeFile, lpszProcessName) == 0)
			{
				return pe32.th32ProcessID;
			}
		} while (Process32Next(hSnapshot, &pe32));
	}

	throw std::exception("Can't find the process!");
}
