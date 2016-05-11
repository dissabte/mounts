//! \cond INTERNAL

/*!
 * \file MountWatcherImpl.cpp
 * Contains MountWatcher Linux implementation.
 * \warning This file is not a part of watcher library public interface.
 */

#include "MountWatcherImpl.h"
#include "MountInfoReader.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>

const char* MountWatcher::Implementation::kPathToWatch = "/proc/self/mountinfo";
const std::chrono::milliseconds MountWatcher::Implementation::kPollingPeriod = std::chrono::milliseconds(50);

MountWatcher::Implementation::Implementation(const MountWatcher& watcher)
    : _watcher(watcher)
    , _stop(false)
    , _thread(&Implementation::run, this)
{
}

MountWatcher::Implementation::~Implementation()
{
	_stop = true;
	_thread.join();
}

void MountWatcher::Implementation::run() const
{
	MountInfoReader mountInfoReader;
	std::set<std::string> oldPaths = mountInfoReader.readMountedPaths(MountInfoReader::kMediaPrefix);

	while (!_stop)
	{
		std::set<std::string> newPaths = mountInfoReader.readMountedPaths(MountInfoReader::kMediaPrefix);

		std::set<std::string> unmountedPaths;
		std::set<std::string> mountedPaths;
		std::set_difference(std::begin(oldPaths), std::end(oldPaths), std::begin(newPaths), std::end(newPaths), std::inserter(unmountedPaths, std::begin(unmountedPaths)));
		std::set_difference(std::begin(newPaths), std::end(newPaths), std::begin(oldPaths), std::end(oldPaths), std::inserter(mountedPaths, std::begin(mountedPaths)));
		oldPaths.swap(newPaths);

		if (!unmountedPaths.empty())
		{
			for (const std::string& path : unmountedPaths)
			{
				MountNotificationData data;
				data.properties.emplace(std::string("path"), path);
				data.properties.emplace(std::string("device"), mountInfoReader.getDeviceForMountedPath(path));
				_watcher.notifyObservers(MountNotificationType::DEVICE_UNMOUNTED, data);
			}
		}

		if (!mountedPaths.empty())
		{
			for (const std::string& path : mountedPaths)
			{
				MountNotificationData data;
				data.properties.emplace(std::string("path"), path);
				data.properties.emplace(std::string("device"), mountInfoReader.getDeviceForMountedPath(path));
				_watcher.notifyObservers(MountNotificationType::DEVICE_MOUNTED, data);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(kPollingPeriod));
	}
}

//! \endcond
