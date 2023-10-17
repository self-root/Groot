#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include "VPNCore_global.h"
#include <QSettings>
#include <QJsonObject>

class VPNCORE_EXPORT DeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = nullptr);
    QString getManufasturer();
    QString getModel();
    QString makeDeviceId();
    QString getDeviceId();
    QString deviceName();
    QJsonObject toJson();

private:
    QSettings mSettings;
signals:

};

#endif // DEVICEMANAGER_H
