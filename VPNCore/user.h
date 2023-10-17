#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QDate>
#include "VPNCore_global.h"

namespace AnVPN {
class VPNCORE_EXPORT User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString email READ getEmail WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString token READ getToken WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString endSub READ getEndSub WRITE setEndSub NOTIFY endSubChanged)
public:
    explicit User(QObject *parent = nullptr);

    QString getEmail() const;
    void setEmail(const QString &newEmail);

    QString getPassword() const;
    void setPassword(const QString &newPassword);

    QString getToken() const;
    void setToken(const QString &newToken);

    QJsonObject toJsonObject() const;

    QString getEndSub() const;
    void setEndSub(const QString &newEndSub);

private:
    QString email;
    QString password;
    QString token;
    QDate endSub;

signals:
    void emailChanged();
    void passwordChanged();
    void tokenChanged();
    void endSubChanged();

};
}



#endif // USER_H
