#pragma once

#include <QObject>
#include <mounts/MountWatcher.h>

class MountWatcherProxy : public QObject
{
	Q_OBJECT

public:
	explicit MountWatcherProxy(const MountWatcher& watcher);
	virtual ~MountWatcherProxy() = default;

	Q_INVOKABLE void forcedUpdate() const;

private:
	const MountWatcher& _watcher;
};
