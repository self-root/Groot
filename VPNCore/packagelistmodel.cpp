#include "packagelistmodel.h"
#include <QJniObject>
#include <QtCore/QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSettings>

namespace AnVPN {
PackageListModel::PackageListModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}


int PackageListModel::rowCount(const QModelIndex &parent) const
{
    return mPackages.size();
}



QVariant PackageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    Package pkg = mPackages.at(row);
    switch (role) {
    case NameRole:
        return pkg.name;
        break;
    case PackageRole:
        return pkg.package;
        break;
    case ExcludedRole:
        return pkg.excluded;
        break;
    default:
        return QVariant();
        break;
    }

}

QHash<int, QByteArray> PackageListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "appName";
    roles[PackageRole] = "packageName";
    roles[ExcludedRole] = "excluded";

    return roles;
}

void PackageListModel::getAppLists()
{
    QJniObject packages = QJniObject::callStaticMethod<jstring>(
        "xyz/irootsoftware/device/Device",
        "getInstalledApps",
        "(Landroid/content/Context;)Ljava/lang/String;",
        QNativeInterface::QAndroidApplication::context());

    QJsonArray jArr = QJsonDocument::fromJson(packages.toString().toStdString().c_str()).array();
    getExpluded();
    beginResetModel();
    mPackages.clear();
    for (int i = 0; i < jArr.size(); i++)
    {
        Package pkg;
        auto ex = jArr.at(i).toObject();
        pkg.name = ex["appName"].toString();
        pkg.package = ex["packageName"].toString();

        if (excluded.contains(pkg.package))
            pkg.excluded = true;
        else
            pkg.excluded = false;

        mPackages.push_back(pkg);
    }
    endResetModel();

}

void PackageListModel::getExpluded()
{
    QSettings settings;
    int arrSize = settings.beginReadArray("excluded");
    excluded.clear();
    for (int i = 0; i < arrSize; i++)
    {
        settings.setArrayIndex(i);
        excluded.append(settings.value("package").toString());
    }
    settings.endArray();
}

void PackageListModel::saveExpluded()
{
    QSettings settings;
    settings.beginWriteArray("excluded", excluded.size());

    for (int i = 0; i < excluded.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("package", excluded.at(i));
    }

    settings.endArray();
}

}

