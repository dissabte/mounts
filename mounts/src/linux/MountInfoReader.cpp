//! \cond INTERNAL

/*!
 * \file MountInfoReader.cpp
 * Contains MountInfoReader implementation.
 * \warning This file is not a part of watcher library public interface.
 */

#include "MountInfoReader.h"

const std::string MountInfoReader::kMediaPrefix = "/media";

MountInfoReader::MountInfoReader()
    : _file("/proc/self/mountinfo")
{
}

MountInfoReader::~MountInfoReader()
{
}

std::set<std::string> MountInfoReader::readMountedPaths(const std::string& prefix)
{
	std::set<std::string> result;
	Action collectPathsWithPrefix = std::bind(&MountInfoReader::collectMountedPathsWithPrefix, this, std::placeholders::_1, std::ref(prefix), std::ref(result));
	traverseMountInfo(collectPathsWithPrefix);
	return result;
}

std::string MountInfoReader::getDeviceForMountedPath(const std::string& path)
{
	std::string result;
	Action findDevice = std::bind(&MountInfoReader::findMountSourceForMountedPath, this, std::placeholders::_1, std::ref(path), std::ref(result));
	traverseMountInfo(findDevice);
	return result;
}

void MountInfoReader::traverseMountInfo(MountInfoReader::Action action)
{
	if (_file.is_open())
	{
		_file.clear();
		_file.seekg(0, std::ios_base::beg);

		while (!_file.eof())
		{
			MountInfo info;
			_file >> info;

			if (!info.mount_point.empty())
			{
				action(info);
			}
		}
	}
}

void MountInfoReader::collectMountedPathsWithPrefix(const MountInfo& info, const std::string& prefix, std::set<std::string>& paths)
{
	if (info.mount_point.find(prefix) == 0)
	{
		// dirty: since this MountInfo isn't used anywhere else I move from it instead of copying
		paths.emplace(std::move(info.mount_point));
	}
}

void MountInfoReader::findMountSourceForMountedPath(const MountInfo& info, const std::string& path, std::string& device)
{
	if (info.mount_point == path)
	{
		// dirty: since this MountInfo isn't used anywhere else I move from it instead of copying
		device = std::move(info.mount_source);
	}
}

//! \endcond
