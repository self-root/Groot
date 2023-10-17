#include "vpnmanager.h"
#include <QJsonObject>
#include <QDebug>
#include "vpnconfig.h"
#include <QCoreApplication>

namespace AnVPN {
VPNManager::VPNManager(QObject *parent)
    : QObject{parent}, traffic(new Traffic(vpnCore))
{
    QCoreApplication::setApplicationName("Groot");
    QCoreApplication::setOrganizationName("irootsoftware");
    user = new User;
    QObject::connect(&apiCaller, &APICaller::basicLoginSuccessfull, this, &VPNManager::onBasicLoginSuccessfull);
    QObject::connect(&apiCaller, &APICaller::loginSuccessfull, this, &VPNManager::onLoginSuccess);
    QObject::connect(&apiCaller, &APICaller::invalidToken, this, &VPNManager::needToLogin);
    QObject::connect(&apiCaller, &APICaller::invalidCredentials, this, &VPNManager::loginFailure);
    QObject::connect(&apiCaller, &APICaller::unverifiedUser, this, &VPNManager::verifyUser);
    QObject::connect(&apiCaller, &APICaller::signupSuccess, this, &VPNManager::verifyUser);
    QObject::connect(&apiCaller, &APICaller::emailVerified, this, &VPNManager::needToLogin);
    QObject::connect(&apiCaller, &APICaller::userConfDownloaded, this, &VPNManager::onUserConfDownloaded);
    QObject::connect(&vpnCore, &VPNCore::tunnelConnected, this, &VPNManager::onTunnelConnected);
    QObject::connect(&vpnCore, &VPNCore::tunnelDisconnected, this, &VPNManager::onTunnelDisconnected);
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
        auto deviceId = deviceManager.toJson();
        apiCaller.getConf(deviceId, *this->user);
    }


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
    VPNConfig vConf;
    vConf.setConf(conf);
    vpnCore.setConfig(vConf);
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

}


