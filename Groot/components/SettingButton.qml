import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: menuItem
    property alias iconText: icon.text
    property alias iconColor: icon.color
    property alias iconFont: icon.font.family
    property alias text: txt.text
    property alias color: txt.color
    property alias bgColor: rect_.color
    property alias pixelSize: txt.font.pixelSize
    height: 45
    width: parent.width
    signal clicked()
    Rectangle{
        id: rect_
        anchors.fill: parent
        anchors.margins: 3
        color: "#1a1a1a"

        Text {
            id: txt
            anchors.left: parent.left
            anchors.leftMargin: 6
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: icon
            anchors.right: parent.right
            anchors.rightMargin: 6
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: txt.font.pixelSize
        }

        Behavior on color{
            SmoothedAnimation{

            }
        }



        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                menuItem.clicked()
            }

            onEntered: {
                rect_.color = Qt.darker("#0073dd")
            }

            onExited: {
                rect_.color = 'black'
            }
        }
    }
}
