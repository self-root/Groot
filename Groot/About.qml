import QtQuick 2.15
import QtQuick.Controls 2.15
import "components"

Item {
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
        text: "About"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }


    Image {
        id: appLogo
        anchors.top: pageTitle.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 200
        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/groot.png"
    }

    Text {
        id: appName
        anchors.top: appLogo.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: uicontroller.appName
        color: "white"
        font.pixelSize: 16
    }

    Text {
        id: aboutTxt
        anchors.top: appName.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "A secure VPN client app"
        color: "white"
        font.pixelSize: 14
    }

    Text {
        id: author
        anchors.top: aboutTxt.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Created by VAOHITA Ivan Oscar"
        color: "white"
        font.pixelSize: 14
    }

    Text {
        id: credit
        anchors.top: author.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Credit: ----"
        color: "white"
        font.pixelSize: 14
    }

    Text {
        id: copyrightTxt
        anchors.top: credit.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Copyright © 2023 irootsoftware"
        color: "white"
        font.pixelSize: 14
    }
}
