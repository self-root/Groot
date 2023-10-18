#ifndef PACKAGELISTMODEL_H
#define PACKAGELISTMODEL_H

#include <QAbstractListModel>
#include "VPNCore_global.h"

namespace AnVPN {

struct Package
{
    QString name;
    QString package;
    bool excluded;
};

class VPNCORE_EXPORT PackageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PackageRoles{
        NameRole = Qt::UserRole + 1,
        PackageRole,
        ExcludedRole
    };
    explicit PackageListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void getAppLists();
    Q_INVOKABLE int search(const QString &appName);
    Q_INVOKABLE void setExcluded(const QString &packageName, bool excluded_);
    Q_INVOKABLE void saveExcluded();

    void getExcluded();

private:
    QStringList excluded;
    std::vector<Package> mPackages;

signals:
    void excludedListUpdated(const QStringList &excludedList);
};

}


#endif // PACKAGELISTMODEL_H
