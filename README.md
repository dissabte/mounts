# mounts library
## General information
Library provides tools to watch for fs mount related notifications (e.g. removable media).

## Pre-requisites
To build mounts I use [cmake](https://cmake.org)<br>
As unit test framework I use [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) which is added as submodule to the mounts repository under `external/unittest-cpp` folder. This one is not required, demo app can be built without it.

## Documenation
The code has doxygen-compatible comments and there's configuration file for doxygen available as well. To generate goxygen documentation one can do following:
~~~bash
# assuming you are in a build folder located next to mounts repository:
cmake ../mounts/mounts/ && cmake --build . --target mounts_docs
~~~

And in case you want to look at internal documentation (i.e. the one for library private parts) just add `-DDOXYGEN_SECTIONS=INTERNAL`:<br>

~~~bash
# assuming you are in a build folder located next to mounts repository:
cmake -DDOXYGEN_SECTIONS=INTERNAL ../mounts/mounts/ && cmake --build . --target mounts_docs
~~~

## Platform support
- Linux - supported
- OS X - not supported yet
- Windows - not supported yet

## Usage examples
Following code will print all device information provided by the system when device will be hot plugged in.
~~~c++
MountWatcher watcher;
watcher.registerObserver(MountNotificationType::DEVICE_MOUNTED, [](const MounNotificationData& data)
{
	std::cout << "Mounted device with following properties:\n";
	std::for_each(std::begin(data.properties),
	              std::end(data.properties),
	              [](const std::pair<std::string, std::string>& i)
	              {
	                  std::cout << "\t" << i.first << ": " << i.second << std::endl;
	              });
	std::cout << std::endl;
});
~~~
Check mounts [demo](https://github.com/dissabte/mounts/blob/master/mounts/demo/cli/main.cpp) app for more info.

