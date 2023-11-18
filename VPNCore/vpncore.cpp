#include "vpncore.h"
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

namespace AnVPN {
VPNCore::VPNCore(QObject *parent)
    : QObject(parent)
{
    wgConnection = QJniObject("xyz/irootsoftware/wireguard/WireguardConnection",
                              "(Landroid/content/Context;)V",
                              QNativeInterface::QAndroidApplication::context());

    tunnelWatcher = new TunnelWatcher(wgConnection);
    QObject::connect(tunnelWatcher, &TunnelWatcher::connected, this, &VPNCore::tunnelConnected);
    QObject::connect(tunnelWatcher, &TunnelWatcher::disconnected, this, &VPNCore::tunnelDisconnected);
}

void VPNCore::setConfig(const VPNConfig &conf)
{
    this->mConfig = conf.toStringJson();
    qDebug() << __FUNCTION__ << mConfig;
}

void VPNCore::connect()
{
    if (wgConnection.isValid())
    {
        QJniObject jConf = QJniObject::fromString(mConfig);
        wgConnection.callMethod<void>("setConfig",
                                      "(Ljava/lang/String;)V",
                                      jConf.object<jstring>());
        wgConnection.callMethod<void>("startConnection");
    }
}

void VPNCore::disconnect()
{
    wgConnection.callMethod<void>("disconnect");
}

void VPNCore::reconnect()
{
    if (!mConfig.isEmpty())
    {
        this->disconnect();
        this->connect();
    }
}

double VPNCore::getUpTraffic()
{
    jlong up = wgConnection.callMethod<jlong>("getTransmittedTraffic");

    return up;
}

double VPNCore::getDownTraffic()
{
    jlong down = wgConnection.callMethod<jlong>("getReceivedTraffic");

    return down;
}
}
