import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
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
        text: "DNS"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }

    ButtonGroup{
        id: dnsBtnGroup
    }

    ListView{
        id: dnslistView
        anchors.top: pageTitle.bottom
        anchors.topMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        model: vpnmanager.dnsListModel

        delegate: RadioDelegate{
            width: parent.width
            text: dnsname
            ButtonGroup.group: dnsBtnGroup
            checked: currentdns

            onClicked: {
                console.log("Clicked: " + dnsname)
                vpnmanager.changeDns(dnsname)
            }
        }

    }
}
