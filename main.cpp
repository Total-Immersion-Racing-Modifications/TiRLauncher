#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>

#include "viewmodels/registered_enums.h"
#include "viewmodels/main_window_vm.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	qmlRegisterType<ScreenRatioPresetType>("launcher.enums", 1, 0, "ScreenRatioPresetType");
	qmlRegisterType<MainWindowVM>("launcher.vms", 1, 0, "MainWindowVM");

	QGuiApplication app(argc, argv);

	app.setOrganizationName("R2 Company");
	app.setOrganizationDomain("r2.company");

	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
	for (const QString &locale : uiLanguages) {
		const QString baseName = "TiR_Launcher_" + QLocale(locale).name();
		if (translator.load(":/i18n/" + baseName)) {
			app.installTranslator(&translator);
			break;
		}
	}

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/views/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
