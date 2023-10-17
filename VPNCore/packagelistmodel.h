#ifndef PACKAGELISTMODEL_H
#define PACKAGELISTMODEL_H

#include <QAbstractItemModel>
#include "VPNCore_global.h"

namespace AnVPN {

struct Package
{
    QString name;
    QString package;
    bool excluded;
};

class VPNCORE_EXPORT PackageListModel : public QAbstractItemModel
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

    void getAppLists();
    void getExpluded();
    void saveExpluded();

private:
    QStringList excluded;
    std::vector<Package> mPackages;
};

}


#endif // PACKAGELISTMODEL_H
