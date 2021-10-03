#include "tir_launcher.h"

#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <string>
#include <tlhelp32.h>

namespace tir
{

TiRLauncher::TiRLauncher()
	: _tir_proc_name("tir.exe")
	, _process(std::make_unique<QProcess>())
	, _mods_manager(std::make_unique<ModsManager>())
	, _first_address(0x51a3c8 + 0x4)
	, _second_address(0x51a408 + 0x4)
	, _third_address(0x51a3ec)
{

}

void TiRLauncher::set_screen_ratio_preset(const ScreenRatioPreset &preset) noexcept
{
	_screen_ratio_preset = preset;
}

QString TiRLauncher::get_path_to_game() const noexcept
{
	return _path_to_game;
}

void TiRLauncher::set_path_to_game(const QString& path_to_game) noexcept
{
	_path_to_game = path_to_game;
}

void TiRLauncher::start_game() noexcept
{
	try
	{
		if (_path_to_game.length() == 0)
		{
			throw std::exception("You didn't choose game folder!");
		}
		const QString path_to_exe(_path_to_game + "/" + _tir_proc_name);
		QDesktopServices::openUrl(QUrl::fromLocalFile(path_to_exe));
		const auto proc_pid = get_pid_by_process_name(_tir_proc_name.toStdWString().c_str());
		const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_pid);
		if (hProcess == NULL)
		{
			CloseHandle(hProcess);
			throw std::exception("Can't open the target process!");
		}
		WriteProcessMemory(hProcess, (LPVOID)_first_address, &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)_second_address, &_screen_ratio_preset.first, sizeof(_screen_ratio_preset.first), 0);
		WriteProcessMemory(hProcess, (LPVOID)_third_address, &_screen_ratio_preset.second, sizeof(_screen_ratio_preset.second), 0);
		inject_mods(hProcess);
		CloseHandle(hProcess);
	}
	catch (std::exception& e)
	{
		qDebug() << "Failed to start game: " << e.what();
	}
}

DWORD TiRLauncher::get_pid_by_process_name(const wchar_t *lpszProcessName)
{
	PROCESSENTRY32 pe32 = { 0 };

	pe32.dwSize = sizeof(PROCESSENTRY32);

	const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
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

void TiRLauncher::inject_mods(const HANDLE hProcess)
{
	const auto mods_files = _mods_manager->get_mods_folder();

	const LPVOID lpLoadLibrary = get_LoadLibraryA();
	if (lpLoadLibrary == NULL)
	{
		CloseHandle(hProcess);
		throw std::exception("Can't get the LoadLibraryA address!");
	}
	for (const auto& mod_file_path : mods_files)
	{
		const char* sDLLName = mod_file_path.c_str();
		const DWORD dwSize = strlen(sDLLName) + 1;
		const LPVOID lpDllName = VirtualAllocEx(hProcess, NULL, dwSize,
			MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (lpDllName == NULL)
		{
			CloseHandle(hProcess);
			throw std::exception("Can't allocate memory in the target process!");
		}
		qDebug() << "Memory allocated at 0x" << lpDllName;

		BOOL bRes = WriteProcessMemory(hProcess, lpDllName, sDLLName,
			dwSize, NULL);
		if (!bRes)
		{
			VirtualFreeEx(hProcess, lpDllName, dwSize, MEM_RELEASE);
			CloseHandle(hProcess);
			throw std::exception("Can't write the dll name in the target process!");
		}

		const HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
			LPTHREAD_START_ROUTINE(lpLoadLibrary), lpDllName, 0, 0);
		if (hThread == NULL)
		{
			VirtualFreeEx(hProcess, lpDllName, dwSize, MEM_RELEASE);
			CloseHandle(hProcess);
			throw std::exception("Can't create remote thread!");
		}

		VirtualFreeEx(hProcess, lpDllName, dwSize, MEM_RELEASE);
		qDebug() << "Mode" << mod_file_path.c_str() << "is injected!";
	}
}

const LPVOID TiRLauncher::get_LoadLibraryA()
{

	const HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	if (hKernel32 == NULL)
	{
		qDebug() << "Can't get the handle of kernel32.dll!";
		return NULL;
	}

	const LPVOID lpLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");
	if (lpLoadLibrary == NULL)
	{
		qDebug() << "Can't get the LoadLibraryA address!";
		return NULL;
	}
	return lpLoadLibrary;
}

} // namespace tir
