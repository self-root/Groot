#ifndef DNSLISTMODEL_H
#define DNSLISTMODEL_H

#include <QAbstractListModel>
#include <QSettings>

namespace AnVPN {
class DNS
{
public:
    DNS(QString name, QString primaryDNS, QString secondaryDNS);
    QString name;
    QString primaryDNS;
    QString secondaryDNS;
    QString info;
    bool current = false;
};

class DNSListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DNSRole{
        NameRole = Qt::UserRole + 1,
        PrimaryRole,
        SecondaryRole,
        InfoRole,
        CurrentRole
    };
    explicit DNSListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool setCurrentDNS(const QString &dnsName);

    QPair<QString, QString> getDns(const QString &dnsName);

private:
    QList<DNS> dnsList;
    QSettings setting;
    QString currentDNS;

    void initDNS();
    void setCurrentValue(const QString &DNSName, bool value);
};
}


#endif // DNSLISTMODEL_H
