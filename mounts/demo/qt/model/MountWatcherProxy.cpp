#include "MountWatcherProxy.h"

MountWatcherProxy::MountWatcherProxy(const MountWatcher& watcher)
    : _watcher(watcher)
{
}

void MountWatcherProxy::forcedUpdate() const
{
	_watcher.forcedUpdate();
}
