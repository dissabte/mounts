#pragma once

/*!
 * \file MountWatcher.h
 * Contains MountWatcher implementation - Observable that informs about filesystem mount related notifications.
 */

#include "Observable.h"
#include "MountNotification.h"
#include <memory>

/*!
 * \class MountWatcher MountWatcher.h <watcher/MountWatcher.h>
 * \brief The MountWatcher class is Observable that watches for mount related notifications
 *
 * MountWatcher will inform registered observers about mount/unmount events.
 *
 * \sa MountNotificationType, MountNotificationData, Observable
 */

class MountWatcher : public Observable<MountNotificationType, MountNotificationData>
{
public:
	/*!
	 * \brief DeviceWatcher constructor
	 */
	explicit MountWatcher();
	/*!
	 * \brief ~DeviceWatcher destructor
	 */
	virtual ~MountWatcher();

	/*!
	 * \brief Forces sending DEVICE_MOUNTED notification for every mounted media device
	 */
	void forcedUpdate() const;

private:
	class Implementation;
	std::shared_ptr<Implementation> _impl;
};
