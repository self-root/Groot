#include "vpnmanager.h"
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>

namespace AnVPN {
VPNManager::VPNManager(QObject *parent)
    : QObject{parent}, traffic(new Traffic(vpnCore)),
      packageModel(new PackageListModel()),
      mDeviceListModel(new DeviceListModel()),
      mDnsListModel(new DNSListModel())
{
    QCoreApplication::setApplicationName("Groot");
    QCoreApplication::setOrganizationName("irootsoftware");
    user = new User;
    QObject::connect(&apiCaller, &APICaller::basicLoginSuccessfull, this, &VPNManager::onBasicLoginSuccessfull);
    QObject::connect(&apiCaller, &APICaller::loginSuccessfull, this, &VPNManager::onLoginSuccess);
    QObject::connect(&apiCaller, &APICaller::invalidToken, this, &VPNManager::needToLogin);
    QObject::connect(&apiCaller, &APICaller::loginFailure, this, &VPNManager::loginFailure);
    QObject::connect(&apiCaller, &APICaller::unverifiedUser, this, &VPNManager::verifyUser);
    QObject::connect(&apiCaller, &APICaller::signupSuccess, this, &VPNManager::verifyUser);
    QObject::connect(&apiCaller, &APICaller::emailVerified, this, &VPNManager::needToLogin);
    QObject::connect(&apiCaller, &APICaller::codeNotMatch, this, &VPNManager::verificationCodeNotMatch);
    QObject::connect(&apiCaller, &APICaller::userConfDownloaded, this, &VPNManager::onUserConfDownloaded);
    QObject::connect(&apiCaller, &APICaller::deviceListReady, mDeviceListModel, &DeviceListModel::setDevices);
    QObject::connect(&apiCaller, &APICaller::deviceRemoved, this, &VPNManager::onDeviceRemoved);
    QObject::connect(&apiCaller, &APICaller::userConflict, this, &VPNManager::userConflict);
    QObject::connect(&apiCaller, &APICaller::resetPasswordMailSent, this, &VPNManager::pwdResetMailSent);
    QObject::connect(&apiCaller, &APICaller::requestPasswordMailFail, this, &VPNManager::pwdResetMailFail);
    QObject::connect(&apiCaller, &APICaller::passwordReset, this, &VPNManager::passwordReset);
    QObject::connect(&apiCaller, &APICaller::passwordResetFail, this, &VPNManager::passwordResetFail);
    QObject::connect(&vpnCore, &VPNCore::tunnelConnected, this, &VPNManager::onTunnelConnected);
    QObject::connect(&vpnCore, &VPNCore::tunnelDisconnected, this, &VPNManager::onTunnelDisconnected);
    QObject::connect(packageModel, &PackageListModel::excludedListUpdated, this, &VPNManager::onExcludedListUpdated);
    QObject::connect(&secretSevice, &SecretService::removed, this, &VPNManager::needToLogin);
    secretSevice.setAlias("anvpnlogin");
}

void VPNManager::login(const QString &mail, const QString &password)
{
    user->setEmail(mail);
    user->setPassword(password);
    apiCaller.login(*user);
}

void VPNManager::signup(const QString &mail, const QString &password)
{
    user->setEmail(mail);
    user->setPassword(password);
    apiCaller.signup(*user);

}

void VPNManager::verifyMail(const QString &code)
{
    if (!code.isEmpty())
        apiCaller.verifyMail(this->user->getEmail(), code);
}

void VPNManager::connect()
{
    qDebug() << "CurrentState: " << mTunnelState;
    if (mTunnelState == 1)
    {
        qDebug() << "Disconnecting";
        vpnCore.disconnect();
    }

    else
    {
        qDebug() << "Connecting";
        auto excuded = VPNConfig::getExcludedApp();
        config.addExcluded(excuded);
        auto deviceId = deviceManager.toJson();
        apiCaller.getConf(deviceId, *this->user);
    }
}

void VPNManager::getUserDevices()
{
    apiCaller.getDevices(*user);
}

void VPNManager::removeDevice(const QString &deviceId)
{
    apiCaller.removeDevice(*user, deviceId);
}

void VPNManager::logout()
{
    QString deviceId = deviceManager.getDeviceId();
    if (mTunnelState == 1)
    {
        qDebug() << "Disconnecting";
        vpnCore.disconnect();
    }
    removeDevice(deviceId);
    QSettings set;
    set.remove("deviceID");
    secretSevice.remove();

}

void VPNManager::changeDns(const QString &dnsName)
{
    qDebug() << __FUNCTION__ << dnsName;
    if (mDnsListModel->setCurrentDNS(dnsName))
    {
        config.setDNS(mDnsListModel->getDns(dnsName));
        vpnCore.setConfig(config);
        if (mTunnelState == 1)
        {
            vpnCore.reconnect();
        }
    }


}

void VPNManager::requestPwdResetMail(const QString &email)
{
    this->user->setEmail(email);
    apiCaller.requestResetPwdMail(email);
}

void VPNManager::resetPassword(const QString &newPassword, const QString &verifcode)
{
    if (user->getEmail().isEmpty() || newPassword.isEmpty() || verifcode.isEmpty())
        return;
    QJsonObject form;
    form["mail"] = user->getEmail();
    form["verifcode"] = verifcode;
    form["pwd"] = newPassword;
    apiCaller.resetPassword(form);
}

void VPNManager::getToken()
{
    QObject::connect(&secretSevice, &SecretService::restored, this, [this](const QString &tooken){
        this->user->setToken(tooken);
        if (tooken.isEmpty())
            emit tokenEmpty();
        else
            this->apiCaller.login(user->getToken());

    });
    secretSevice.restore();
}

void VPNManager::saveToken()
{
    secretSevice.setSecret(this->user->getToken());
    secretSevice.store();
}

User *VPNManager::getUser()
{
    return this->user;
}

Traffic *VPNManager::getTraffic()
{
    return traffic;
}

PackageListModel *VPNManager::packageListModel()
{
    return packageModel;
}

DeviceListModel *VPNManager::devicelistModel()
{
    return mDeviceListModel;
}

DNSListModel *VPNManager::dnsListModel()
{
    return mDnsListModel;
}

int VPNManager::tunnelState() const
{
    return mTunnelState;
}

void VPNManager::setTunnelState(int newTunnelState)
{

    if (newTunnelState != mTunnelState)
    {
        mTunnelState = newTunnelState;
        emit tunnelStateChanged();
    }
}

void VPNManager::onDeviceRemoved(const QString &deviceId)
{
    qDebug() << "Device deleted: " << deviceId;
    getUserDevices();
}

void VPNManager::onBasicLoginSuccessfull(const QJsonObject &data)
{
    qDebug() << "User connected: " << data;
    this->user->setToken(data["token"].toString());
    this->saveToken();
    this->user->setEndSub(data["end_sub"].toString());
    emit loginSuccess();
}

void VPNManager::onLoginSuccess(const QJsonObject &data)
{
    this->user->setEmail(data["mail"].toString());
    this->user->setEndSub(data["end_sub"].toString());
    emit loginSuccess();
}

void VPNManager::onUserConfDownloaded(const QJsonObject &conf)
{
    config.setConf(conf);
    vpnCore.setConfig(config);
    vpnCore.connect();
}

void VPNManager::onTunnelConnected()
{
    setTunnelState(1);
}

void VPNManager::onTunnelDisconnected()
{
    setTunnelState(0);
}

void VPNManager::onExcludedListUpdated(const QStringList &excluded)
{
    qDebug() << "Adding excluded: " << excluded;
    config.addExcluded(excluded);
    if (mTunnelState == 1)
    {
        vpnCore.disconnect();
        vpnCore.setConfig(config);
        vpnCore.connect();
    }
}
}
