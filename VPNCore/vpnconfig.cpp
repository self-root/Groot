#include "vpnconfig.h"
#include <QJsonDocument>

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
    return QJsonDocument(config).toJson();
}

}

