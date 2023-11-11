import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "components"

Page {
    Material.theme: Material.Dark
    Material.accent: "#4361ee"
    anchors.fill: parent

    Connections{
        target: vpnmanager
        function onVerificationCodeNotMatch(){
            dialog.title = "Code Mismatch"
            dialog.text = "Code  entered does not match"
            dialog.open()
        }
    }
    Dialog{
        property alias text: dialogText.text
        id: dialog
        anchors.centerIn: parent
        Text {
            id: dialogText
            anchors.centerIn: parent
        }
    }
    Column{
        anchors.centerIn: parent
        spacing: 6
        Text {
            color: "white"
            font.pixelSize: 18
            text: qsTr("Enter verification code sent to:")
        }
        Text {
            color: "white"
            font.pixelSize: 18
            text: vpnmanager.user.email
        }
        LineEdit{
            id: code
            width: parent.width
            placeholder: "Code"
        }
        SimpleButton{
            text: "Activate"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("Validated")
                vpnmanager.verifyMail(code.text)
            }
        }
    }
}
