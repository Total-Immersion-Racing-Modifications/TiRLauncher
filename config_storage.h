#ifndef CONFIGSTORAGE_H
#define CONFIGSTORAGE_H

#include <QObject>
#include <QFile>

class ConfigStorage : public QObject
{
	Q_OBJECT
public:
	explicit ConfigStorage();

signals:

private:
	QFile _config_file;
};

#endif // CONFIGSTORAGE_H
