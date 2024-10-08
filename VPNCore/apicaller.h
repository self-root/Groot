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
    void requestResetPwdMail(const QString &email);
    void resetPassword(const QJsonObject &obj);

private:
    QString host = "api.irootsoftware.com";
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
    void onRequestResetEmail();
    void passwordResetReply();

signals:
    void loginSuccessfull(const QJsonObject &data);
    void basicLoginSuccessfull(const QJsonObject &data);
    void badRequest();
    void unverifiedUser();
    void invalidToken();
    void loginFailure(const QString &message);
    void invalidCredentials();
    void serverError(const QString &error, int errorCode);
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
    void resetPasswordMailSent();
    void requestPasswordMailFail();
    void passwordReset();
    void passwordResetFail();
};

}


#endif // APICALLER_H
