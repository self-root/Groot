#include "dnslistmodel.h"

namespace AnVPN {
DNSListModel::DNSListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    initDNS();
}

int DNSListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dnsList.size();
}

QVariant DNSListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    DNS currentRow = dnsList.at(row);
    switch (role) {
    case NameRole:
        return currentRow.name;

    case PrimaryRole:
        return currentRow.primaryDNS;

    case SecondaryRole:
        return currentRow.secondaryDNS;

    case InfoRole:
        return currentRow.info;

    case CurrentRole:
        return currentRow.current;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DNSListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "dnsname";
    roles[PrimaryRole] = "primarydns";
    roles[SecondaryRole] = "secondarydns";
    roles[InfoRole] = "info";
    roles[CurrentRole] = "currentdns";

    return roles;
}

bool DNSListModel::setCurrentDNS(const QString &dnsName)
{
    if (dnsName == currentDNS)
        return false;
    setting.setValue("dns", dnsName);
    setCurrentValue(currentDNS, false);
    currentDNS = dnsName;
    setCurrentValue(currentDNS, true);
    qDebug() << __FUNCTION__ << " DNS changed";
    return true;
}

QPair<QString, QString> DNSListModel::getDns(const QString &dnsName)
{
    for (auto &dns: dnsList)
    {
        if (dns.name == dnsName)
            return QPair<QString, QString>{dns.primaryDNS, dns.secondaryDNS};
    }
    return QPair<QString, QString>{"",""};
}

void DNSListModel::initDNS()
{
    currentDNS = setting.value("dns", "Cloudflare").toString();
    dnsList.append({
        DNS("Google", "8.8.8.8", "8.8.4.4"),
        DNS("Cloudflare", "1.1.1.1", "1.0.0.1"),
        DNS("OpenDNS", "208.67.222.222", "208.67.220.220"),
        DNS("OpenDNS family shield", "208.67.222.123", "208.67.220.123"),
        DNS("AdGuard DNS", "94.140.14.14", "94.140.15.15"),
        DNS("CleanBrowsing", "185.228.168.9", "185.228.169.9")
    });

    setCurrentValue(currentDNS, true);
}

void DNSListModel::setCurrentValue(const QString &DNSName, bool value)
{
    for (auto &dns : dnsList)
    {
        if (dns.name == DNSName)
        {
            dns.current = value;
            break;
        }
    }
}

DNS::DNS(QString name, QString primaryDNS, QString secondaryDNS)
    : name(name), primaryDNS(primaryDNS), secondaryDNS(secondaryDNS)
{

}

}


