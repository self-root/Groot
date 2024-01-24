#include "packagelistmodel.h"
#include <QJniObject>
#include <QtCore/QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSettings>
#include <algorithm>

namespace AnVPN {
PackageListModel::PackageListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


int PackageListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mPackages.size();
}



QVariant PackageListModel::data(const QModelIndex &index, int role) const
{
    //if (!index.isValid())
    //    return QVariant();

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
    getExcluded();
    beginResetModel();
    mPackages.clear();
    for (int i = 0; i < jArr.size(); i++)
    {
        Package pkg;
        auto ex = jArr.at(i).toObject();
        pkg.name = ex["appName"].toString();
        pkg.package = ex["packageName"].toString();

        //qDebug() << pkg.name << " == " << pkg.package;
        //if (pkg.name == pkg.package)

        if (excluded.contains(pkg.package))
        {
            pkg.excluded = true;
            mPackages.insert(mPackages.begin(), pkg);
        }
        else
        {
            pkg.excluded = false;
            mPackages.push_back(pkg);
        }
    }
    std::sort(mPackages.begin() + excluded.size(), mPackages.end(),
              [](const Package &a, const Package &b){
                  return a.name < b.name;
              });
    endResetModel();

}

int PackageListModel::search(const QString &appName)
{
    for (std::size_t i = 0; i < mPackages.size(); i++)
    {
        if (mPackages.at(i).name.contains(appName, Qt::CaseInsensitive))
            return i;
    }
    return -1;
}

void PackageListModel::setExcluded(const QString &packageName, bool excluded_)
{
    for (auto &p : mPackages)
    {
        if (p.package == packageName)
        {
            p.excluded = excluded_;
            if (excluded_ == false)
            {
                excluded.removeIf([&](const QString &pkg){
                    return pkg == packageName;
                });
            }
            else {
                excluded.append(packageName);
            }
            return;
        }
    }

}

void PackageListModel::getExcluded()
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

void PackageListModel::saveExcluded()
{
    QSettings settings;
    settings.remove("excluded");
    settings.sync();
    settings.beginWriteArray("excluded", excluded.size());

    for (int i = 0; i < excluded.size(); i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("package", excluded.at(i));
        qDebug() << "Setting value: " << excluded.at(i);
    }

    settings.endArray();
    settings.sync();

    emit excludedListUpdated(this->excluded);
}

}

