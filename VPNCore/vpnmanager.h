#ifndef VPNMANAGER_H
#define VPNMANAGER_H

#include <QObject>
#include <QString>
#include "VPNCore_global.h"
#include "apicaller.h"
#include "secretservice.h"
#include "user.h"
#include "devicemanager.h"
#include "vpncore.h"
#include "traffic.h"

namespace AnVPN {
class VPNCORE_EXPORT VPNManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(User *user READ getUser CONSTANT)
    Q_PROPERTY(int tunnelState READ tunnelState WRITE setTunnelState NOTIFY tunnelStateChanged)
    Q_PROPERTY(Traffic *traffic READ getTraffic CONSTANT)
public:
    explicit VPNManager(QObject *parent = nullptr);
    Q_INVOKABLE void login(const QString &mail, const QString &password);
    Q_INVOKABLE void signup(const QString &mail, const QString &password);
    Q_INVOKABLE void verifyMail(const QString &code);
    Q_INVOKABLE void connect();
    void getToken();
    void saveToken();
    User *getUser();
    Traffic *getTraffic();

    int tunnelState() const;
    void setTunnelState(int newTunnelState);

signals:
    void loginSuccess();
    void loginFailure();
    void verifyUser();
    void userLoggedOut();
    void vpnConnected();
    void vpnDisconnected();
    void tokenEmpty();
    void needToLogin();
    void signedUp();
    void tunnelStateChanged();

private:
    APICaller apiCaller;
    SecretService secretSevice;
    User *user;
    DeviceManager deviceManager;
    VPNCore vpnCore;
    int mTunnelState = 0;
    Traffic *traffic;
private slots:
    void onBasicLoginSuccessfull(const QJsonObject &data);
    void onLoginSuccess(const QJsonObject &data);
    void onUserConfDownloaded(const QJsonObject &conf);
    void onTunnelConnected();
    void onTunnelDisconnected();
};
}



#endif // VPNMANAGER_H
