import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property alias iconText: icn.text
    property alias iconFont: icn.font.family
    property alias iconSize: icn.font.pixelSize
    property alias text: txt.text
    property alias trText: traffic.text
    width: 90
    height: 60
    Rectangle{
        anchors.fill: parent
        color: "transparent"
        radius: 6
        anchors.margins: 4

        Text {
            id: icn
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 18
            color: "white"

        }

        Text {
            id: txt
            anchors.left: icn.right
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.leftMargin: 6
            color: "grey"
        }

        Text {
            id: traffic
            anchors.left: icn.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            anchors.leftMargin: 6
            color: "white"
            font.bold: true

        }
    }
}
