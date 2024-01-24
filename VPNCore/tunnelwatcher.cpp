#include "tunnelwatcher.h"
#include <QDebug>

namespace AnVPN {
TunnelWatcher::TunnelWatcher(QJniObject &wg, QObject *parent)
    : QObject{parent}, mWg(wg)
{
    QObject::connect(&stateTimer, &QTimer::timeout, this, &TunnelWatcher::readState);
    stateTimer.start(500);
}

void TunnelWatcher::readState()
{
    int res = mWg.callMethod<jint>("getTunSTate");

    if (res != state)
    {
        qDebug() << "Tunne; state changed from " << state << " to " << res;
        state = res;
        if (res == 1)
            emit connected();
        else if (res == 0)
            emit disconnected();
    }
}

}

