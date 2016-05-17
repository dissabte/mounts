#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <mounts/MountWatcher.h>
#include <mounts/MountNotification.h>

#include "model/MountModel.h"
#include "model/MountEntry.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	MountModel model;

	MountWatcher watcher;
	watcher.registerObserver(MountNotificationType::DEVICE_MOUNTED, [&model](const MountNotificationData& notification)
	{
		QString path;
		QString device;

		if (notification.properties.count("path"))
		{
			path = QString::fromUtf8(notification.properties.at("path").c_str());
		}
		if (notification.properties.count("device"))
		{
			device = QString::fromUtf8(notification.properties.at("device").c_str());
		}
		if (!path.isEmpty())
		{
			emit model.mountEntryAppeared(path, device);
		}
	});

	watcher.registerObserver(MountNotificationType::DEVICE_UNMOUNTED, [&model](const MountNotificationData& notification)
	{
		QString path;
		if (notification.properties.count("path"))
		{
			path = QString::fromUtf8(notification.properties.at("path").c_str());
		}
		if (!path.isEmpty())
		{
			emit model.mountEntryDisappeared(path);
		}
	});

	engine.rootContext()->setContextProperty("mountsModel", &model);
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

	return app.exec();
}
