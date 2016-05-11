//! \cond INTERNAL

/*!
 * \file MountInfo.cpp
 * \warning This file is not a part of watcher library public interface.
 *
 * Contains operators to read/write MountInfo structure from/to a stream
 */

#include "MountInfo.h"
#include <iostream>

std::istream& operator>>(std::istream& input, MountInfo& mountInfo)
{
	input >> mountInfo.mount_id;
	input >> mountInfo.parent_id;
	input >> mountInfo.st_dev;
	input >> mountInfo.root;
	input >> mountInfo.mount_point;
	input >> mountInfo.mount_options;

	std::string currentOption;
	while (!input.eof())
	{
		input >> currentOption;
		if (currentOption != "-")
		{
			mountInfo.optional.push_back(currentOption);
		}
		else
		{
			break;
		}
	};

	input >> mountInfo.fs_type;
	input >> mountInfo.mount_source;
	input >> mountInfo.super_options;
	return input;
}

std::ostream& operator<<(std::ostream& input, const MountInfo& mountInfo)
{
	input << mountInfo.mount_id << " ";
	input << mountInfo.parent_id << " ";
	input << mountInfo.st_dev << " ";
	input << mountInfo.root << " ";
	input << mountInfo.mount_point << " ";
	input << mountInfo.mount_options << " ";

	for (const std::string& opt : mountInfo.optional)
	{
		input << opt << " ";
	}

	input << "- ";

	input << mountInfo.fs_type << " ";
	input << mountInfo.mount_source << " ";
	input << mountInfo.super_options << " ";
	return input;
}

//! \endcond
