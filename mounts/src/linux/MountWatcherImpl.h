#pragma once

//! \cond INTERNAL

/*!
 * \file MountWatcherImpl.h
 * Contains MountWatcher Linux implementation.
 * \warning This file is not a part of watcher library public interface.
 */

#include <mounts/MountWatcher.h>
#include <thread>
#include <chrono>
#include <atomic>

/*!
 * \class MountWatcher::Implementation MountWatcherImpl.h "MountWatcherImpl.h"
 * \brief The MountWatcher::Implementation class is Linux implementation of MountWatcher
 * \sa HotPlugWatcher, MountWatcher
 * \warning This class is not a part of watcher library public interface.
 */

class MountWatcher::Implementation
{
	static const char* kPathToWatch;                       //!< The path to watch for, equals `/proc/self/mountinfo`
	static const std::chrono::milliseconds kPollingPeriod; //!< Polling period, default value is 50ms

public:
	/*!
	 * \brief Implementation constructor
	 * \param watcher reference to the MountWatcher instance. Needed to call notifyObservers().
	 *
	 * Starts separate thread that periodically polls /proc/self/mountinfo with kPollingPeriod interval.
	 */
	Implementation(const MountWatcher& watcher);

	/*!
	 * \brief Implementation destructor
	 */
	~Implementation();

private:
	void run() const;

private:
	const MountWatcher&  _watcher;

	std::atomic<bool>    _stop;
	std::thread          _thread;
};

//! \endcond
