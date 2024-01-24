import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects
import "components"

Item {
    id: root
    Material.theme: Material.Dark
    Material.accent: "#0073dd"
    //anchors.fill: parent

    FontLoader{
        id: webFont
        source: "qrc:/assets/webfont.ttf"
    }

    ParallelAnimation{
        id: innerRinngAnnimation
        running: false

        NumberAnimation {
            target: innerRing
            property: "width"
            duration: 600
            easing.type: Easing.InOutQuad
            to: 140
        }

        NumberAnimation {
            target: innerRing
            property: "height"
            duration: 600
            easing.type: Easing.InOutQuad
            to: 140
        }

        NumberAnimation {
            target: innerRing
            property: "radius"
            duration: 600
            easing.type: Easing.InOutQuad
            to: 70
        }

        onFinished: {
            innerRing.width = 98

            innerRing.radius = 49
        }
    }

    Rectangle{
        id: p
        anchors.fill: parent
        color: "black"


    }

    IconButton{
        id: settingIcon
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 4
        iconText: "\uf013"
        iconFont: webFont.name
        iconColor: "white"
        pixelSize: 18
        onClicked: {
            uicontroller.toSettings()
        }
    }

    Text {
        id: appName
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: settingIcon.verticalCenter
        text: "StealthLink"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }

    Text {
        id: endsub
        anchors.top: appName.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 25
        text: "Subscried until " + vpnmanager.user.endSub
        color: "white"
        font.pixelSize: 16
    }

    Text {
        id: state
        anchors.top: endsub.bottom
        anchors.topMargin: 16
        anchors.horizontalCenter: parent.horizontalCenter
        text: "<font color='white'> Status | </font>" +
              (vpnmanager.tunnelState === 1 ? "<b><font color='#0073dd'>Connected</font></b>":
                                              "<b><font color='#dc2f02'>Disconnected</font></b>")
        font.pixelSize: 16
    }

    Rectangle{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        height: 200
        AnimatedImage{
            id: animation
            anchors.fill: parent
            source: "qrc:/assets/giphy2.gif"
            playing: vpnmanager.tunnelState
        }
    }

    Rectangle{
        id: outerRing
        width: 160
        height: width
        anchors.centerIn: parent
        radius: 80
        color: connectButton.border.color


    }
    DropShadow{
        anchors.fill: outerRing
        color: connectButton.border.color
        source: outerRing
        horizontalOffset: 0
        verticalOffset: 0
        radius: 20
    }
    Rectangle{
        id: connectButton
        anchors.centerIn: parent
        width: 160
        height: width
        radius: 80
        color: "black"
        border.width: 10
        border.color: vpnmanager.tunnelState === 1 ? "#0073dd" : "#dc2f02"
        Rectangle{
            id: innerRing
            anchors.centerIn: parent
            width: 98
            height: width
            radius: 49
            color: connectButton.border.color
            opacity: 0.6
            visible: width < 140 ? true : false
        }


        Image {
            id: iconImg
            anchors.centerIn: parent
            source: vpnmanager.tunnelState === 1 ? "qrc:/assets/power.svg"
                                                   : "qrc:/assets/power-off.svg"
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                vpnmanager.connect()
            }

            onEntered: {
                innerRinngAnnimation.running = true
            }

        }
        Behavior on border.color{
            PropertyAnimation{

            }
        }

        Behavior on width {
            PropertyAnimation{

            }
        }

        Behavior on height {
            PropertyAnimation{

            }
        }
        Behavior on radius {
            PropertyAnimation{

            }
        }
    }

    Rectangle{
        id: separator
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: connectButton.bottom
        anchors.topMargin: 50
        height: 55
        width: 1
        color: connectButton.border.color
    }

    TrafficIndicator{
        anchors.right: separator.left
        anchors.rightMargin: 1
        anchors.verticalCenter: separator.verticalCenter
        iconText: "\uf093"
        iconFont: webFont.name
        text: "Up"
        trText: vpnmanager.traffic.upTraffic
    }



    TrafficIndicator{
        anchors.left: separator.right
        anchors.leftMargin: 1
        anchors.verticalCenter: separator.verticalCenter
        iconText: "\uf019"
        iconFont: webFont.name
        text: "Down"
        trText: vpnmanager.traffic.downTraffic
    }

}
