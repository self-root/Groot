import QtQuick 2.15
import QtQuick.Controls 2.15


ApplicationWindow {
    id: mainApp
    visible: true
    title: "AnnoyingVPN"
    width: 400
    height: 500

    Connections{
        target: uicontroller
        function onToMainView(){
            mainStackView.replace("qrc:/App.qml")
        }

        function onToLoginView(){
            mainStackView.replace("qrc:/LoginScreen.qml")
        }

        function onToVerificationView(){
            mainStackView.push("qrc:/VerificationScreen.qml")
        }

        function onToPwdReset(){
            mainStackView.push("qrc:/ResetPasswordScreen.qml")
        }
    }

    StackView{
        id: mainStackView
        anchors.fill: parent
        initialItem: "qrc:/SplashScreen.qml"
        //initialItem: "qrc:/App.qml"
        //initialItem: "qrc:/VerificationScreen.qml"
    }

    onClosing: {
        uicontroller.back()
        close.accepted = false
    }
}
