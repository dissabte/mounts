#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <mounts/MountWatcher.h>
#include <mounts/MountNotification.h>

#include "model/MountModel.h"
#include "model/MountEntry.h"
#include "model/MountWatcherProxy.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine;

	// Model for the qml view
	MountModel model;

	// Creating mount watcher and adding observer callbacks
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

	MountWatcherProxy proxy(watcher);

	engine.rootContext()->setContextProperty("mountsModel", &model);
	engine.rootContext()->setContextProperty("mountsWatcher", &proxy);
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

	watcher.forcedUpdate(); // This will send DEVICE_MOUNTED notification for all currently mounted media devices

	return app.exec();
}
