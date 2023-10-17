#include "traffic.h"
#include <QDebug>

namespace AnVPN{
Traffic::Traffic(VPNCore &vCore, QObject *parent)
    : QObject{parent}, vpnCore(vCore)
{
    QObject::connect(&trafficTimer, &QTimer::timeout, this, &Traffic::onTraficTimer);
    QObject::connect(&vpnCore, &VPNCore::tunnelConnected, this, &Traffic::startTrafficTimer);
    QObject::connect(&vpnCore, &VPNCore::tunnelDisconnected, this, &Traffic::stopTrafficTimer);
    //trafficTimer.start(1000);
}

void Traffic::onTraficTimer()
{
    double down = vpnCore.getDownTraffic();
    double up = vpnCore.getUpTraffic();
    qDebug() << "Up: " << up << " Down: " << down;
    downTraffic = (down - previousDown);
    //setDownTraffic(tmpDown);
    upTraffic = (up - previousUp);
    previousDown = down;
    previousUp = up;
    //setUpTraffic(tmpUp);


    if (downTraffic < 1000)
        setDownTraffic( QString("%1 B/s").arg(downTraffic));

    else if(downTraffic >= 1000 && downTraffic < 1000000)
        setDownTraffic(QString("%1 KB/s").arg(qRound(downTraffic/1000)));

    else{
        setDownTraffic(QString("%1 MB/s").arg(qRound(downTraffic/1000000)));
    }

    if (upTraffic < 1000)
        setUpTraffic(QString("%1 B/s").arg(upTraffic));

    else if(upTraffic >= 1000 && upTraffic < 1000000)
        setUpTraffic(QString("%1 KB/s").arg(qRound(upTraffic/1000)));

    else{
        setUpTraffic(QString("%1 MB/s").arg(qRound(upTraffic/1000000)));
    }


}

void Traffic::startTrafficTimer()
{
    trafficTimer.start(1400);
}

void Traffic::stopTrafficTimer()
{
    setUpTraffic(0);
    setDownTraffic(0);
    previousDown = 0;
    previousUp = 0;
    trafficTimer.stop();
    setDownTraffic("0 B/s");
    setUpTraffic("0 B/s");

}

QString Traffic::getDownTraffic() const
{
    return DownTrafficStr;
}

void Traffic::setDownTraffic(QString newDownTraffic)
{
    if (newDownTraffic == DownTrafficStr)
        return;
    DownTrafficStr = newDownTraffic;
    emit downTrafficChanged();
}

QString Traffic::getUpTraffic() const
{
    return upTrafficStr;
}

void Traffic::setUpTraffic(QString newUpTraffic)
{
    if (newUpTraffic == upTrafficStr)
        return;
    upTrafficStr = newUpTraffic;
    emit upTrafficChanged();
}
}

