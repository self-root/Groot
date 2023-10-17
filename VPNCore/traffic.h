#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <QObject>
#include "VPNCore_global.h"
#include "vpncore.h"
#include <QTimer>

namespace AnVPN {
class VPNCORE_EXPORT Traffic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString upTraffic READ getUpTraffic WRITE setUpTraffic NOTIFY upTrafficChanged)
    Q_PROPERTY(QString downTraffic READ getDownTraffic WRITE setDownTraffic NOTIFY downTrafficChanged)
public:
    explicit Traffic(VPNCore &vCore, QObject *parent = nullptr);
    VPNCore &vpnCore;
    QString getUpTraffic() const;
    void setUpTraffic(QString newUpTraffic);

    QString getDownTraffic() const;
    void setDownTraffic(QString newDownTraffic);

private slots:
    void onTraficTimer();
    void startTrafficTimer();
    void stopTrafficTimer();
private:
    QTimer trafficTimer;
    double upTraffic = 0;
    double downTraffic = 0;
    double previousDown = 0;
    double previousUp = 0;
    QString upTrafficStr = "0 B/s";
    QString DownTrafficStr = "0 B/s";
signals:
    void upTrafficChanged();
    void downTrafficChanged();
};

}


#endif // TRAFFIC_H
