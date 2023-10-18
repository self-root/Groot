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
        text: "Devices"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }

    ListView{
        id: listView
        anchors.top: pageTitle.bottom
        anchors.topMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        model: vpnmanager.devicelistModel
        clip: true
        spacing: 6
        delegate: SwipeDelegate{
            id: swipeDelegate
            width: listView.width
            height: 140

            //text: deviceName
            contentItem: Rectangle{
                //anchors.fill: swipeDelegate

                color: "transparent"
                Text {
                    id: dName
                    anchors.top: parent.top
                    anchors.topMargin: 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: deviceName
                    color: "#0073dd"
                    font.pixelSize: 16
                    font.bold: true
                }

                Text {
                    id: dOs
                    anchors.top: dName.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 6
                    anchors.leftMargin: 6
                    text: "OS: " + deviceOS
                    color: "white"
                    font.pixelSize: 14
                }

                Text {
                    id: tType
                    anchors.top: dOs.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 6
                    anchors.leftMargin: 6
                    text: "Device type: " + deviceType
                    color: "white"
                    font.pixelSize: 14
                }

                Text {
                    id: dId
                    anchors.top: tType.bottom
                    anchors.left: parent.left
                    anchors.topMargin: 6
                    anchors.leftMargin: 6
                    text: "ID: " + deviceId
                    color: "white"
                    font.pixelSize: 14
                }
            }

            swipe.right: Label{
                id: deleteLabel
                text: "Delete"
                verticalAlignment: Label.AlignVCenter
                anchors.right: parent.right
                color: "white"
                height: parent.height
                background: Rectangle{
                    color: "red"
                }

                SwipeDelegate.onClicked: {
                    console.log("Remove: " + deviceId)
                    vpnmanager.removeDevice(deviceId)
                }

            }

        }
    }

}
