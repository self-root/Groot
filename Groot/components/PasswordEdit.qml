import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Item {
    id: w
    property alias caption: field.placeholderText
    property alias placeholder: field.placeholderText
    property alias text: field.text
    implicitHeight: c.implicitHeight
    FontLoader{
        id: webfont
        source: "qrc:/assets/webfont.ttf"
    }

    Column{
        id: c
        spacing: 0
        TextField{
            id: field
            width: w.width
            placeholderText: "Password"
            echoMode: TextInput.Password
            clip: true

            Rectangle{
                width: eye.width
                height: eye.height
                color: "transparent"
                anchors.right: parent.right
                anchors.rightMargin: 4
                //anchors.verticalCenter: field.verticalCenter
                anchors.top: parent.top
                anchors.topMargin: 32

                Label{
                    id: eye
                    text: field.echoMode == TextInput.Password? "\uf070" : "\uf06e"
                    //font.family: Style.ifont
                    font.family: webfont.name
                    clip: true

                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (field.echoMode == TextInput.Password){
                            field.echoMode = TextInput.Normal
                        }
                        else{
                            field.echoMode = TextInput.Password
                        }
                    }
                }
            }
        }
    }
}
