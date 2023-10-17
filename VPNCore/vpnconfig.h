#ifndef VPNCONFIG_H
#define VPNCONFIG_H

#include "VPNCore_global.h"
#include <QObject>
#include <QJsonObject>

namespace AnVPN {
class VPNCORE_EXPORT VPNConfig : public QObject
{
    Q_OBJECT
public:
    explicit VPNConfig(QObject *parent = nullptr);
    void setConf(const QJsonObject &jconf);
    /**
     * @brief toStringJson, convert the configuration parameters into a json format string
     * @return A QString containing the configuration
     */
    QString toStringJson() const;

private:
    QJsonObject config;

signals:

};
}



#endif // VPNCONFIG_H
