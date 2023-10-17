import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: icnButton
    property alias iconText: icnTxt.text
    property alias iconFont: icnTxt.font.family
    property alias iconColor: icnTxt.color
    property alias pixelSize: icnTxt.font.pixelSize
    signal clicked()
    width: 40
    height: width
    Rectangle{
        id: icnRect
        anchors.fill: parent
        color: "transparent"
        Text {
            id: icnTxt
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                icnTxt.color = "#0073dd"
            }

            onExited: {
                icnTxt.color = "white"
            }

            onClicked: {
                icnButton.clicked()
            }

        }
    }
}
