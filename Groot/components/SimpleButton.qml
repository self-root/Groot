import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: btn
    property alias text: btnLabel.text
    property alias color1: gstop1.color
    property alias color2: gstop2.color
    signal clicked()
    height: 40
    width: 200
    Rectangle{
        id: btnRect
        radius: 6
        //rotation: 90
        anchors.fill: parent
        gradient: Gradient{
            orientation: Gradient.Horizontal
            GradientStop{
                id: gstop1
                position: 0
                color: "#763e3e"
            }
            GradientStop{
                id: gstop2
                position: 1
                color: "#291c4b"
            }
        }

        Label{
            id: btnLabel
            anchors.centerIn: parent
            font.bold: true
        }

        PropertyAnimation{
            id: ann
            running: false
            target: gstop2
            property: "color"
            from: color2
            to: color1
        }

        PropertyAnimation{
            id: ann2
            running: false
            target: gstop2
            property: "color"
            from: color1
            to: color2
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {

                ann.running = true
                //gstop2.color = "#763e3e"
                //gstop1.color = "#763e3e"
                //gstop1.color = Qt.darker("#763e3e")
                //gstop2.color = Qt.darker("#291c4b")
            }
            onExited: {
                ann2.running = true
                //gstop2.color = "#291c4b"
                //gstop1.color = "#763e3e"
            }
            onClicked:
            {
                btn.clicked()
            }



        }
    }
}
