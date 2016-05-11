#pragma once

/*!
 * \file MountNotification.h
 */

#include <map>
#include <string>

/*!
 * \enum MountNotificationType
 * All notifications that DeviceWatcher can inform of.
 */
enum class MountNotificationType
{
	UNKNOWN,         //!< Default notification type as a placeholder for "all other notifications"
	DEVICE_MOUNTED,  //!< Mass storage device was mounted
	DEVICE_UNMOUNTED //!< Mass storage device was unmounted
};

/*!
 * \class MountNotificationData MountNotification.h <watcher/MountNotification.h>
 * \brief The MountNotificationData struct consists of a associative container of device properties
 */
struct MountNotificationData
{
	std::map<std::string, std::string> properties;
};
