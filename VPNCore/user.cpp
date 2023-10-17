#include "user.h"
#include <QDateTime>

namespace AnVPN {
User::User(QObject *parent)
    : QObject{parent}
{

}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &newEmail)
{
    if (email != newEmail)
    {
        email = newEmail;
        emit emailChanged();
    }

}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    if (password != newPassword)
    {
        password = newPassword;
        emit passwordChanged();
    }

}

QString User::getToken() const
{
    return token;
}

void User::setToken(const QString &newToken)
{
    if (token != newToken)
    {
        token = newToken;
        emit tokenChanged();
    }

}

QJsonObject User::toJsonObject() const
{
    QJsonObject json;
    json["mail"] = this->email;
    json["pwd"] = this->password;
    return json;
}

QString User::getEndSub() const
{
    if (endSub.isValid())
        return endSub.toString("MMMM dd, yyyy");
    return "---";
}

void User::setEndSub(const QString &newEndSub)
{

    endSub = QDate::fromString(newEndSub, "MMMM dd, yyyy");
    qDebug() << "New endSub: " << newEndSub;
    qDebug() << "End_sub: " << endSub;
    emit endSubChanged();
}

}

