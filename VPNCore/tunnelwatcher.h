#ifndef TUNNELWATCHER_H
#define TUNNELWATCHER_H

#include <QObject>
#include <QTimer>
#include <QJniObject>
#include "VPNCore_global.h"

namespace AnVPN {
class VPNCORE_EXPORT TunnelWatcher : public QObject
{
    Q_OBJECT
public:
    explicit TunnelWatcher(QJniObject &wg, QObject *parent = nullptr);

private:
    int state = 0;
    QTimer stateTimer;
    QJniObject &mWg;

public slots:
    void readState();

signals:
    void connected();
    void disconnected();

};

}


#endif // TUNNELWATCHER_H
