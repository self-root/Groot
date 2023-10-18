#include "devicelistmodel.h"
#include <QJsonArray>
#include <QJsonObject>

namespace AnVPN {
DeviceListModel::DeviceListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DeviceListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    return devices.size();

    // FIXME: Implement me!
}

QVariant DeviceListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    Device device = devices.at(row);
    qDebug() << "D_ID: " << device.id;

    switch (role) {
    case IdRole:
        return device.id;
        break;
    case OSRole:
        return device.os;
        break;
    case NameRole:
        return device.name;
        break;
    case TypeRole:
        return device.type;
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> DeviceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "deviceId";
    roles[OSRole] = "deviceOS";
    roles[NameRole] = "deviceName";
    roles[TypeRole] = "deviceType";

    return roles;
}

void DeviceListModel::setDevices(const QJsonArray &devicesArr)
{
    qDebug() << __FUNCTION__ << devicesArr;
    beginResetModel();
    devices.clear();
    for (auto &d : devicesArr)
    {
        Device device;
        QJsonObject dObject = d.toObject();
        device.id = dObject["device_id"].toString();
        device.name = dObject["device_name"].toString();
        device.type = dObject["device_type"].toString();
        device.os = dObject["device_os"].toString();

        devices.push_back(device);
        qDebug() << "QJsonObject: " << dObject;
        qDebug() << "Device loaded: " << device.name;
    }
    endResetModel();

    qDebug() << "Reset model finished: " << devices.size();
}

}

