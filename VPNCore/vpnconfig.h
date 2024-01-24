#ifndef VPNCONFIG_H
#define VPNCONFIG_H

#include "VPNCore_global.h"
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

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

    void addExcluded(const QStringList excluded);

    static QStringList getExcludedApp();

    void setDNS(const QPair<QString, QString> &dns);

private:
    QJsonObject config;
    QStringList excludedApp;
    QPair<QString, QString> mDns;
signals:

};
}



#endif // VPNCONFIG_H
