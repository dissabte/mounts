#pragma once

#include <QString>

class MountEntry
{
public:
	MountEntry(const QString& path, const QString& device);

	QString path() const;
	QString device() const;

	bool operator==(const MountEntry& other) const;

private:
	QString _path;
	QString _device;
};
