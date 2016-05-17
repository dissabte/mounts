#include "MountEntry.h"

MountEntry::MountEntry(const QString &path, const QString& device)
    : _path(path)
    , _device(device)
{
}

QString MountEntry::path() const
{
	return _path;
}

QString MountEntry::device() const
{
	return _device;
}

bool MountEntry::operator==(const MountEntry& other) const
{
	return _path == other._path;
}
