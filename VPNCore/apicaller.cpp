#include "apicaller.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


namespace AnVPN {
APICaller::APICaller(QObject *parent)
    : QObject{parent}
{

}

void APICaller::login(const User &user)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/login")));
    QString credentials = user.getEmail() + ":" + user.getPassword();
    auto auth = "Basic " + QByteArray(credentials.toStdString().c_str()).toBase64();
    request.setRawHeader(QByteArray("Authorization"), auth);
    qDebug() << __FUNCTION__ << "Login: " << auth;
    QNetworkReply *reply = networkmanager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::basicloginReply);
}

void APICaller::login(const QString &token)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/login")));
    auto auth = "Bearer " + QByteArray(token.toStdString().c_str());
    request.setRawHeader("Authorization", auth);
    QNetworkReply *reply = networkmanager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::loginReply);

}

void APICaller::signup(const User &user)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/signup")));
    request.setRawHeader("content-type", "application/json");
    QJsonDocument jDoc(user.toJsonObject());
    QNetworkReply *reply = networkmanager.post(request, QByteArray(jDoc.toJson(QJsonDocument::Compact)));
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::signupReply);
}

void APICaller::verifyMail(const QString &email, const QString &code)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/mail/verify")));
    request.setRawHeader("content-type", "application/json");
    QJsonObject json;
    json["mail"] = email;
    json["code"] = code;
    QNetworkReply *reply = networkmanager.post(request, QByteArray(QJsonDocument(json).toJson(QJsonDocument::Compact)));
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::mailVerificationReply);
}

void APICaller::getConf(const QJsonObject &obj, const User &user)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/userconf")));
    request.setRawHeader("content-type", "application/json");
    auto auth = "Bearer " + QByteArray(user.getToken().toStdString().c_str());
    request.setRawHeader("Authorization", auth);

    QNetworkReply *reply = networkmanager.post(request, QByteArray(QJsonDocument(obj).toJson(QJsonDocument::Compact)));
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::userConfReply);
}

void APICaller::getDevices(const User &user)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3").arg(host, port, "/vpn/devices")));
    auto auth = "Bearer " + QByteArray(user.getToken().toStdString().c_str());
    request.setRawHeader("Authorization", auth);

    QNetworkReply *reply = networkmanager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::getDevicesReply);
}

void APICaller::removeDevice(const User &user, const QString &deviceId)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("https://%1:%2/%3/%4").arg(host, port, "/vpn/devices/delete/", deviceId)));
    auto auth = "Bearer " + QByteArray(user.getToken().toStdString().c_str());
    request.setRawHeader("Authorization", auth);

    QNetworkReply *reply = networkmanager.deleteResource(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &APICaller::removeDeviceReply);
}

void APICaller::basicloginReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statsCode = attr.toInt();

        if (statsCode == 200)
        {
            qDebug() << "Login successfull";
            auto res = reply->readAll();
            QJsonObject data = QJsonDocument::fromJson(res).object();
            qDebug() << "Data: " << data;
            emit basicLoginSuccessfull(data);
        }

        else if (statsCode == 400) {
            qDebug() << __FUNCTION__ << " Bad request";
            emit badRequest();
        }

        else if (statsCode == 401) {
            emit invalidCredentials();
        }

        else if (statsCode == 403) {
            emit unverifiedUser();
        }

        else
        {
            qDebug() << __FUNCTION__ << " Unknown error: " << statsCode;
            emit serverError();
        }
    }
}

void APICaller::loginReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statsCode = attr.toInt();

        if (statsCode == 200)
        {
            qDebug() << __FUNCTION__ << "Login successfull";
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonObject obj = jDoc.object();
            qDebug() << "Date: " << obj["end_sub"].toString();
            emit loginSuccessfull(obj);
        }
        else if (statsCode == 400) {
            qDebug() << __FUNCTION__ << " Bad request";
            emit badRequest();
        }
        else if (statsCode == 401) {
            //auto res = reply->readAll();
            //QJsonObject data = QJsonDocument::fromJson(res).object();
            emit invalidToken();
        }

        else
        {
            qDebug() << __FUNCTION__ << " Unknown error: " << statsCode;
            emit serverError();
        }
    }
}

void APICaller::signupReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:
            emit signupSuccess();
            break;
        case 400:
            qDebug() << __FUNCTION__ << "Bad request...";
            break;
        case 409:
            qDebug() << __FUNCTION__ << "User already exist...";
            emit userConflict();
            break;
        case 413:
            qDebug() << __FUNCTION__ << "Payload too large...";
            break;
        default:
            qDebug() << __FUNCTION__ << "ERROR: " << statusCode;
            break;
        }
    }
}

void APICaller::mailVerificationReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:
            emit emailVerified();
            break;
        case 401:
            qDebug() << __FUNCTION__ << "Verification code expired";
            emit codeExpired();
            break;
        case 403:
            qDebug() << __FUNCTION__ << "Verification code does not match";
            emit codeNotMatch();
            break;
        case 413:
            qDebug() << __FUNCTION__ << "Payload too large...";
            break;
        default:
            qDebug() << __FUNCTION__ << "ERROR: " << statusCode;
            break;
        }
    }
}

void APICaller::userConfReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:{
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonObject conf = jDoc.object();
            qDebug() << "UserCOnf: " << conf;
            emit userConfDownloaded(conf);
            break;
        }
        case 401:
            emit invalidToken();
            break;
        case 403:
            emit excessDevice();
            break;
        default:
            qDebug() << __FUNCTION__ << "ERROR: " << statusCode;
            break;
        }
    }
}

void APICaller::getDevicesReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:{
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonArray devices = jDoc.array();
            emit deviceListReady(devices);
            break;
        }
        case 401:
            emit invalidToken();
            break;
        case 400:
            qDebug() << "Bad request";
            break;
        default:
            qDebug() << __FUNCTION__ << "ERROR: " << statusCode;
            break;
        }
    }

}

void APICaller::removeDeviceReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
    auto attr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (attr.isValid())
    {
        int statusCode = attr.toInt();
        switch (statusCode) {
        case 200:{
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonObject dId = jDoc.object();
            emit deviceRemoved(dId["device"].toString());
            break;
        }
        case 204:{
            QByteArray data = reply->readAll();
            QJsonDocument jDoc = QJsonDocument::fromJson(data);
            QJsonObject dId = jDoc.object();
            emit noDevice(dId["device"].toString());
            break;
        }

        case 401:
            emit invalidToken();
            break;
        case 400:
            qDebug() << "Bad request";
            break;
        default:
            qDebug() << __FUNCTION__ << "ERROR: " << statusCode;
            break;
        }
    }
}
}



