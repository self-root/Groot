#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
//#include "vpncore.h"
#include "vpnmanager.h"
namespace AnVPN {
//class VPNCore;
}

class UIController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ appName CONSTANT)
public:
    explicit UIController(AnVPN::VPNManager &vpnManager_, QObject *parent = nullptr);
    QString appName();
private:
    //AnVPN::VPNCore vpnCore;
    AnVPN::VPNManager &vpnManager;
signals:
    void toMainView();
    void toLoginView();
    void loginFailed();
    void toVerificationView();
    void toSettings();
    void toUserAccount();
    void back();
    void toSplitTunneling();
    void toUserAccountScreen();
    void toDeviceScreen();
    void toAboutScreen();
};

#endif // UICONTROLLER_H
