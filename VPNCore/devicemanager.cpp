#include "devicemanager.h"
#include <QUuid>
#include <QJniObject>

DeviceManager::DeviceManager(QObject *parent)
    : QObject{parent}, mSettings("irootsoftware", "AnnoyingVPN")
{

}

QString DeviceManager::getManufasturer()
{
    QJniObject obj = QJniObject::callStaticMethod<jstring>(
        "xyz/irootsoftware/device/Device",
        "manufacturer"
        );
    return obj.toString();
}

QString DeviceManager::getModel()
{
    QJniObject obj = QJniObject::callStaticMethod<jstring>(
        "xyz/irootsoftware/device/Device",
        "model"
        );
    return obj.toString();
}

QString DeviceManager::makeDeviceId()
{
    QString deviceId = QUuid::createUuid().toString(QUuid::Id128);
    mSettings.setValue("deviceID", deviceId);
    mSettings.sync();
    return deviceId;
}

QString DeviceManager::getDeviceId()
{
    auto id = mSettings.value("deviceID", "").toString();
    if (id.isEmpty())
        return makeDeviceId();
    return id;
}

QString DeviceManager::deviceName()
{
    return QString("%1 %2").arg(getManufasturer(), getModel());
}

QJsonObject DeviceManager::toJson()
{
    QJsonObject device;
    device["os"] = "Android";
    device["name"] = deviceName();
    device["id"] = getDeviceId();
    device["type"] = "Mobile";

    return device;
}


