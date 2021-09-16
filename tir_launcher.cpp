#include "tir_launcher.h"

#include <QDebug>
#include <QDir>
#include <string>
#include <QUrl>
#include <QDesktopServices>
#include <tlhelp32.h>

TiRLauncher::TiRLauncher()
	: _tir_proc_name("tir.exe")
	, _process(std::make_unique<QProcess>())
{

}

void TiRLauncher::set_screen_ratio_preset(const ScreenRatioPreset &preset) noexcept
{
	_screen_ratio_preset = preset;
}

void TiRLauncher::start_game()
{
	try
	{
		QString pathToExe("D:/Program Files (x86)/Akella Games/Total Immersion Racing/" + _tir_proc_name);
		QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(pathToExe)));
		const auto proc_pid = get_pid_by_process_name(L"tir.exe");
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_pid);
		if (hProcess == NULL)
		{
			qDebug() << "Can't open the target process!";
			CloseHandle(hProcess);
			return;
		}
		WriteProcessMemory(hProcess, (LPVOID)(0x51a3c8 + 0x4), &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)(0x51a408 + 0x4), &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)0x51a3ec, &_screen_ratio_preset.second, sizeof(_screen_ratio_preset.second), 0);
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
