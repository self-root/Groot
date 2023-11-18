#include "vpnconfig.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QSettings>

namespace AnVPN {
VPNConfig::VPNConfig(QObject *parent)
    : QObject{parent}
{

}

void VPNConfig::setConf(const QJsonObject &jconf)
{
    this->config = jconf;
}

QString VPNConfig::toStringJson() const
{

    QJsonObject jobj = config;
    if (!mDns.first.isEmpty() && !mDns.second.isEmpty())
    {
        QJsonArray arr;
        arr.append(mDns.first);
        arr.append(mDns.second);
        jobj["DNS"] = arr;
    }

    jobj["excluded"] = QJsonArray::fromStringList(excludedApp);
    qDebug () << "Add excluded to config: " << excludedApp;
    qDebug() << "Excluded app: " << jobj["excluded"] ;

    return QJsonDocument(jobj).toJson();
}

void VPNConfig::addExcluded(const QStringList excluded)
{
    //config["excluded"] = QJsonArray::fromStringList(excluded);

    //excludedApp = QJsonArray::fromStringList(excluded);
    excludedApp = excluded;
    qDebug() << "Added: " << excludedApp;
}

QStringList VPNConfig::getExcludedApp()
{
    QSettings settings;
    int arrSize = settings.beginReadArray("excluded");
    QStringList excluded;
    for (int i = 0; i < arrSize; i++)
    {
        settings.setArrayIndex(i);
        excluded.append(settings.value("package").toString());
        qDebug() << "Excluded: " << settings.value("package").toString();
    }
    settings.endArray();
    return excluded;
}

void VPNConfig::setDNS(const QPair<QString, QString> &dns)
{
    mDns.first = dns.first;
    mDns.second = dns.second;
}

}

