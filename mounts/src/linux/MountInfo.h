#pragma once

//! \cond INTERNAL

/*!
 * \file MountInfo.h
 * \warning This file is not a part of watcher library public interface.
 *
 * Contains MountInfo structure, that represents data in `/proc/self/mountinfo`
 */

#include <tuple>
#include <string>
#include <vector>

/*!
 * \brief The MountInfo struct represents data in `/proc/self/mountinfo` file.
 * \warning This struct is not a part of watcher library public interface.
 */

struct MountInfo
{
	int mount_id;                      //!< unique identifier of the mount (may be reused after umount)
	int parent_id;                     //!< ID of parent (or of self for the top of the mount tree)
	std::string st_dev;                //!< value of st_dev for files on filesystem in form of "major:minor"
	std::string root;                  //!< root of the mount within the filesystem
	std::string mount_point;           //!< mount point relative to the process's root
	std::string mount_options;         //!< mount options
	std::vector<std::string> optional; //!< zero or more fields of the form "tag[:value]"
	std::string fs_type;               //!< name of filesystem of the form "type[.subtype]"
	std::string mount_source;          //!< filesystem specific information or "none"
	std::string super_options;         //!< super block options

	/*!
	 * \brief MountInfo trivial constructor
	 */
	MountInfo() : mount_id(0), parent_id(0) {}

	friend std::istream& operator>>(std::istream& input, MountInfo& mountInfo);
	friend std::ostream& operator<<(std::ostream& input, const MountInfo& mountInfo);
};

//! \endcond
