#pragma once

//! \cond INTERNAL

/*!
 * \file MountInfoReader.h
 * Contains MountInfoReader implementation.
 * \warning This file is not a part of watcher library public interface.
 */

#include "MountInfo.h"
#include <set>
#include <string>
#include <fstream>
#include <functional>

/*!
 * \class MountInfoReader MountInfoReader.h "MountInfo/MountInfoReader.h"
 * \brief The MountInfoReader has the functionality to read/parse "/proc/self/mountinfo".
 * \warning This class is not a part of watcher library public interface.
 *
 * Since [procfs](https://en.wikipedia.org/wiki/Procfs) does not contains actually files
 * [inotify](https://en.wikipedia.org/wiki/Inotify) can't be used to fatch for changes in
 * [/proc/self/mountinfo](https://www.kernel.org/doc/Documentation/filesystems/proc.txt) file.
  */

class MountInfoReader
{
	using Action = std::function<void (const MountInfo&)>;

public:
	static const std::string kMediaPrefix; //!< Default removable media path prefix - "/media"

public:
	/*!
	 * \brief MountInfoReader constructor
	 */
	MountInfoReader();

	/*!
	 * MountInfoReader destructor
	 */
	~MountInfoReader();

	/*!
	 * \brief readMountedPaths searches for mounted fs which paths start with prefix
	 * \param prefix specified the prefix of the paths to search for.
	 * \return returns the set of mounted fs' paths that start with specified prefix.
	 */
	std::set<std::string> readMountedPaths(const std::string& prefix);

	/*!
	 * \brief getDeviceForMountedPath is used to get the mount source path of the mounted fs path.
	 * \param path mounted fs path.
	 * \return returns the mount source paths for the specified mounted fs path.
	 *
	 * For example, method might return "/dev/sdb1" for path "/media/username/myflashdrive".
	 */
	std::string getDeviceForMountedPath(const std::string& path);

private:
	void traverseMountInfo(Action action);
	void collectMountedPathsWithPrefix(const MountInfo& info, const std::string& prefix, std::set<std::string>& paths);
	void findMountSourceForMountedPath(const MountInfo& info, const std::string& path, std::string& device);

private:
	std::ifstream _file;
};

//! \endcond
