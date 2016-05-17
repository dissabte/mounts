#include <QAbstractListModel>
#include <QModelIndex>
#include <QHash>

#include "MountEntry.h"

class MountModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum MountRoles {
		PathRole = Qt::UserRole + 1,
		DeviceRole
	};

public:
	explicit MountModel(QObject* parent = 0);
	virtual ~MountModel() = default;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	virtual QHash<int, QByteArray> roleNames() const override;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
	void mountEntryAppeared(const QString& path, const QString& device);
	void mountEntryDisappeared(const QString& path);
	void clear();

public slots:
	void onMountEntryAppeared(const QString& path, const QString& device);
	void onMountEntryDisappeared(const QString& path);
	void onClear();

private:
	QList<MountEntry> _mounts;
	QHash<int, QByteArray> _roleNames;
};
