#ifndef CONFIG_STORAGE_VM_H
#define CONFIG_STORAGE_VM_H

#include "config_storage.h"

#include <QObject>

class ConfigStorageVM : public QObject
{
	Q_OBJECT

	using ConfigStoragePtr = std::unique_ptr<ConfigStorage>;

public:
	explicit ConfigStorageVM();

	QString get_game_foler() const noexcept;
	int get_screen_ratio() const noexcept;

public slots:
	void save_game_folder(QString path_to_game_folder) noexcept;
	void save_screen_ratio(int screen_ratio_type) noexcept;

private:
	ConfigStoragePtr _config_storage;
};

#endif // CONFIG_STORAGE_VM_H
