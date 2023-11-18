import QtQuick 2.15
import QtQuick.Controls 2.15
import "components"

Item {
    FontLoader{
        id: webFont
        source: "qrc:/assets/webfont.ttf"
    }
    Rectangle{
        anchors.fill: parent
        color: "black"

    }

    IconButton{
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
        id: title
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Settings")
        color: "white"
        font.bold: true
        font.pixelSize: 18

    }

    Column{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 30
        anchors.leftMargin: 2
        anchors.rightMargin: 2

        SettingButton{
            text: "Account"
            color: "white"
            pixelSize: 18
            iconText: "\uf054"
            iconFont: webFont.name
            iconColor: "white"
            onClicked: {
                uicontroller.toUserAccountScreen()
            }
        }

        SettingButton{
            text: "Split Tunneling"
            color: "white"
            pixelSize: 18
            iconText: "\uf054"
            iconFont: webFont.name
            iconColor: "white"
            onClicked: {
                uicontroller.toSplitTunneling()
            }
        }

        SettingButton{
            text: "Manage devices"
            color: "white"
            pixelSize: 18
            iconText: "\uf054"
            iconFont: webFont.name
            iconColor: "white"

            onClicked: {
                uicontroller.toDeviceScreen()
            }
        }

        SettingButton{
            text: "DNS Server"
            color: "white"
            pixelSize: 18
            iconText: "\uf054"
            iconFont: webFont.name
            iconColor: "white"
            onClicked: {
                uicontroller.toDNSSetting();
            }
        }

        SettingButton{
            text: "Abount"
            color: "white"
            pixelSize: 18
            iconText: "\uf054"
            iconFont: webFont.name
            iconColor: "white"
            onClicked: {
                uicontroller.toAboutScreen()
            }
        }


    }
}
