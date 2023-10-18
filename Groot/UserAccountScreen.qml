import QtQuick 2.15
import QtQuick.Controls 2.15
import "components"

Page {
    Material.theme: Material.Dark
    Material.accent: "#0073dd"

    FontLoader{
        id: webFont
        source: "qrc:/assets/webfont.ttf"
    }
    Rectangle{
        id: p
        anchors.fill: parent
        color: "black"


    }

    IconButton{
        id: backBtn
        iconText: "\uf060"
        iconFont: webFont.name
        iconColor: "white"
        pixelSize: 22
        anchors.left: parent.left
        anchors.verticalCenter: title.verticalCenter
        anchors.leftMargin: 4
        onClicked: {
            uicontroller.back()
        }
    }

    Text {
        id: pageTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: backBtn.verticalCenter
        text: "Account"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }

    Rectangle{
        anchors.top: pageTitle.bottom
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 6
        anchors.rightMargin: 6
        radius: 6
        color: "#0073dd"
        height: 100

        Text {
            id: mailTxt
            text: "User: " + vpnmanager.user.email
            color: "white"
            font.pixelSize: 16
            //font.bold: true
            anchors.top: parent.top
            anchors.topMargin: 6
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: endSubTxt
            anchors.top: mailTxt.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Until " + vpnmanager.user.endSub
            font.pixelSize: 20
            font.bold: true
            color: "white"
        }
    }

    SimpleButton{
        id: logoutBtn
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
        text: "Logout"
        color1: "#dc2f02"
        color2: "#dc2f02"

        onClicked: {
            vpnmanager.logout()
        }
    }
}
