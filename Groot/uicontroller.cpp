#include "uicontroller.h"
#include <QDebug>

UIController::UIController(AnVPN::VPNManager &vpnManager_, QObject *parent)
    : QObject{parent}, vpnManager(vpnManager_)
{
    //vpnCore.connect();
    QObject::connect(&vpnManager, &AnVPN::VPNManager::loginSuccess, this, &UIController::toMainView);
    QObject::connect(&vpnManager, &AnVPN::VPNManager::tokenEmpty, this, &UIController::toLoginView);
    QObject::connect(&vpnManager, &AnVPN::VPNManager::needToLogin, this, &UIController::toLoginView);
    QObject::connect(&vpnManager, &AnVPN::VPNManager::loginFailure, this, &UIController::loginFailed);
    QObject::connect(&vpnManager, &AnVPN::VPNManager::signedUp, this, &UIController::toVerificationView);
    QObject::connect(&vpnManager, &AnVPN::VPNManager::verifyUser, this, &UIController::toVerificationView);
    vpnManager.getToken();
}

QString UIController::appName()
{
    return "StealthLink v1.0.0";
}
