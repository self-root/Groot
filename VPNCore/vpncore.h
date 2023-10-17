#ifndef VPNCORE_H
#define VPNCORE_H

#include "VPNCore_global.h"
#include <QObject>
#include <QString>
#include <QJniObject>
#include "vpnconfig.h"
#include "tunnelwatcher.h"

namespace AnVPN {
#define CORE_VERSION "1.0.0"

class VPNCORE_EXPORT VPNCore : public QObject
{
    Q_OBJECT
public:
    QString vpnCore = "AnnoyingVPN";
    VPNCore(QObject *parent = nullptr);
    /**
     * @brief setConfig, set vpn config file
     * @param conf
     */
    void setConfig(const VPNConfig &conf);

    void connect();
    void disconnect();
    void reconnect();

public slots:
    double getUpTraffic();
    double getDownTraffic();

private:
    QString mConfig;
    QJniObject wgConnection;
    TunnelWatcher *tunnelWatcher = nullptr;
signals:
    void tunnelConnected();
    void tunnelDisconnected();
};

}

#endif // VPNCORE_H
