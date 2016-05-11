#include <mounts/MountWatcher.h>
#include <mounts/MountNotification.h>
#include <iostream>
#include <algorithm>
#include <unistd.h>

void printMountedNotification(const MountNotificationData& notification);
void printUnmountedNotification(const MountNotificationData& notification);

int main()
{
	std::cout << "Listening to mount/unmount events (use Ctrl+C to stop)...\n\n";

	MountWatcher mountWatcher;
	mountWatcher.registerObserver(MountNotificationType::DEVICE_MOUNTED, printMountedNotification);
	mountWatcher.registerObserver(MountNotificationType::DEVICE_UNMOUNTED, printUnmountedNotification);

	// ctrl+c me
	while (true)
	{
		sleep(1);
	}
	return 0;
}


void printMountedNotification(const MountNotificationData& notification)
{
	std::cout << "MOUNTED Device with properties:\n";
	std::for_each(std::begin(notification.properties), std::end(notification.properties), [](auto&& i){ std::cout << "\t" << i.first << ": " << i.second << std::endl; });
	std::cout << std::endl;
}

void printUnmountedNotification(const MountNotificationData& notification)
{
	std::cout << "UNMOUNTED Device with properties:\n";
	std::for_each(std::begin(notification.properties), std::end(notification.properties), [](auto&& i){ std::cout << "\t" << i.first << ": " << i.second << std::endl; });
	std::cout << std::endl;
}
