#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include "VPNCore_global.h"

namespace AnVPN {
struct Device
{
    QString id;
    QString os;
    QString type;
    QString name;
};
class VPNCORE_EXPORT DeviceListModel : public QAbstractListModel
{
    Q_OBJECT


public:
    enum DeviceRoles{
        IdRole = Qt::UserRole + 1,
        OSRole,
        TypeRole,
        NameRole
    };

    explicit DeviceListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

public slots:
    void setDevices(const QJsonArray &devicesArr);

private:
    std::vector<Device> devices;
};
}



#endif // DEVICELISTMODEL_H
