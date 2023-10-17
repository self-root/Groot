#ifndef APICALLER_H
#define APICALLER_H

#include "VPNCore_global.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include "user.h"

namespace AnVPN {
class VPNCORE_EXPORT APICaller : public QObject
{
    Q_OBJECT
public:
    explicit APICaller(QObject *parent = nullptr);

    void login(const User &user);
    void login(const QString &token);
    void signup(const User &user);
    void verifyMail(const QString &email, const QString &code);
    void getConf(const QJsonObject &obj, const User &user);
    void getDevices(const User &user);
    void removeDevice(const User &user, const QString &deviceId);

private:
#ifdef QT_DEBUG
    QString host = "94.176.237.78";
#else
    QString host = "irootsoftware.xyz";
#endif
    QString port = "443";
    QNetworkAccessManager networkmanager;

private slots:
    void basicloginReply();
    void loginReply();
    void signupReply();
    void mailVerificationReply();
    void userConfReply();
    void getDevicesReply();
    void removeDeviceReply();

signals:
    void loginSuccessfull(const QJsonObject &data);
    void basicLoginSuccessfull(const QJsonObject &data);
    void badRequest();
    void unverifiedUser();
    void invalidToken();
    void invalidCredentials();
    void serverError();
    void signupSuccess();
    void userConflict();
    void emailVerified();
    void codeExpired();
    void codeNotMatch();
    void userConfDownloaded(const QJsonObject &conf);
    void excessDevice();
    void deviceListReady(const QJsonArray &devices);
    void deviceRemoved(const QString &deviceId);
    void noDevice(const QString &deviceId);
};

}


#endif // APICALLER_H
