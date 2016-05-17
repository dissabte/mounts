#include "MountModel.h"
#include "MountEntry.h"

MountModel::MountModel(QObject* parent)
    : QAbstractListModel(parent)
{
	_roleNames[PathRole] = "path";
	_roleNames[DeviceRole] = "device";

	connect(this, &MountModel::mountEntryAppeared, this, &MountModel::onMountEntryAppeared);
	connect(this, &MountModel::mountEntryDisappeared, this, &MountModel::onMountEntryDisappeared);
	connect(this, &MountModel::clear, this, &MountModel::onClear);
}

int MountModel::rowCount(const QModelIndex& parent) const
{
	return _mounts.count();
}

QHash<int, QByteArray> MountModel::roleNames() const
{
	return _roleNames;
}

QVariant MountModel::data(const QModelIndex& index, int role) const
{
	if (index.row() >= 0 && index.row() < _mounts.count())
	{
		const MountEntry& entry = _mounts[index.row()];
		switch (role)
		{
		case PathRole:
			return entry.path();
		case DeviceRole:
			return entry.device();
		default:
			break;
		}
	}
	return QVariant();
}

void MountModel::onMountEntryAppeared(const QString& path, const QString& device)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	_mounts << MountEntry(path, device);
	endInsertRows();
}

void MountModel::onMountEntryDisappeared(const QString& path)
{
	int rowIndex = 0;
	for (const MountEntry& entry : _mounts)
	{
		if (entry.path() == path)
		{
			beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
			_mounts.removeOne(entry);
			endRemoveRows();
			break;
		}
		++rowIndex;
	}
}

void MountModel::onClear()
{
	beginRemoveRows(QModelIndex(), 0, rowCount());
	_mounts.clear();
	endRemoveRows();
}
