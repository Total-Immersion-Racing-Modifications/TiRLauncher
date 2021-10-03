#ifndef MODSMANAGER_H
#define MODSMANAGER_H

#include <string>
#include <vector>

#include <QString>

namespace tir
{

class ModsManager
{

	using ModsFiles = std::vector<std::string>;

public:
	ModsManager();
	ModsFiles get_mods_folder() const noexcept;

private:
	void make_mods_files() noexcept;
	bool is_mod(const std::string& file_path);

private:
	ModsFiles _mods_files;
	QString _mods_folder_path;
};

} // namespace tir

#endif // MODSMANAGER_H
