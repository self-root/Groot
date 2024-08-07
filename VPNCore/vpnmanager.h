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
#include "packagelistmodel.h"
#include "vpnconfig.h"
#include "devicelistmodel.h"
#include "dnslistmodel.h"

namespace AnVPN {
class VPNCORE_EXPORT VPNManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(User *user READ getUser CONSTANT)
    Q_PROPERTY(int tunnelState READ tunnelState WRITE setTunnelState NOTIFY tunnelStateChanged)
    Q_PROPERTY(Traffic *traffic READ getTraffic CONSTANT)
    Q_PROPERTY(PackageListModel *packageListModel READ packageListModel CONSTANT)
    Q_PROPERTY(DeviceListModel *devicelistModel READ devicelistModel CONSTANT)
    Q_PROPERTY(DNSListModel *dnsListModel READ dnsListModel CONSTANT)
public:
    explicit VPNManager(QObject *parent = nullptr);
    Q_INVOKABLE void login(const QString &mail, const QString &password);
    Q_INVOKABLE void signup(const QString &mail, const QString &password);
    Q_INVOKABLE void verifyMail(const QString &code);
    Q_INVOKABLE void connect();
    Q_INVOKABLE void getUserDevices();
    Q_INVOKABLE void removeDevice(const QString &deviceId);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void changeDns(const QString &dnsName);
    Q_INVOKABLE void requestPwdResetMail(const QString &email);
    Q_INVOKABLE void resetPassword(const QString &newPassword, const QString &verifcode);
    void getToken();
    void saveToken();
    User *getUser();
    Traffic *getTraffic();
    PackageListModel *packageListModel();
    DeviceListModel *devicelistModel();
    DNSListModel *dnsListModel();

    int tunnelState() const;
    void setTunnelState(int newTunnelState);
public slots:
    void onDeviceRemoved(const QString &deviceId);
signals:
    void loginSuccess();
    void loginFailure(const QString &message);
    void verifyUser();
    void userLoggedOut();
    void vpnConnected();
    void vpnDisconnected();
    void tokenEmpty();
    void needToLogin();
    void signedUp();
    void tunnelStateChanged();
    void userConflict();
    void verificationCodeNotMatch();
    void pwdResetMailSent();
    void pwdResetMailFail();
    void passwordReset();
    void passwordResetFail();

private:
    APICaller apiCaller;
    SecretService secretSevice;
    User *user;
    DeviceManager deviceManager;
    VPNCore vpnCore;
    int mTunnelState = 0;
    Traffic *traffic;
    PackageListModel *packageModel;
    DeviceListModel *mDeviceListModel;
    VPNConfig config;
    DNSListModel *mDnsListModel;
private slots:
    void onBasicLoginSuccessfull(const QJsonObject &data);
    void onLoginSuccess(const QJsonObject &data);
    void onUserConfDownloaded(const QJsonObject &conf);
    void onTunnelConnected();
    void onTunnelDisconnected();
    void onExcludedListUpdated(const QStringList &excluded);
};
}



#endif // VPNMANAGER_H
