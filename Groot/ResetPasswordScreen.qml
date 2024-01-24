import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import "components"

Item {
    Material.theme: Material.Dark
    Material.accent: "#4361ee"
    Connections{
        target: uicontroller
        function onPwdResetFail(){
            resetDialog.title = "Reset failed"
            resetDialog.text = "Code incorrect"
            resetDialog.open()
        }
    }

    Dialog{
        property alias text: dialogText.text
        id: resetDialog
        anchors.centerIn: parent
        Text {
            id: dialogText
            anchors.centerIn: parent
        }
    }

    Rectangle{
        id: parenFormRect
        anchors.fill: parent
        color: "#4361ee"
        Rectangle{
            id: labelRect
            width: welcomLbl.width
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.top: parent.top
            anchors.topMargin: 0
            color: parent.color
            Text{
                id: welcomLbl
                anchors.centerIn: labelRect
                text: "Reset password"
                color: "white"
                font.bold: true
                font.pixelSize: 25
            }
        }


        Rectangle{
            id: formRect
            anchors.top: parent.top
            width: parent.width
            anchors.topMargin: 100
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -40
            color: "#1b1b1b"
            radius: 40
            Rectangle{
                id: signInFormRect
                visible: true
                opacity: 1
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 42
                color: parent.color
                Label{
                    anchors.bottom: codeEdit.top
                    anchors.bottomMargin: 6
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: codeEdit.width
                    text: "Code sent to: " + vpnmanager.user.email
                    wrapMode: Text.WordWrap
                    color: "white"
                }

                LineEdit{
                    id: codeEdit
                    width: parent.width * 0.7
                    anchors.top: parent.top
                    anchors.topMargin: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Verification code"
                }

                PasswordEdit{
                    id: pwdEdit
                    width: parent.width * 0.7
                    anchors.top: codeEdit.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Password"
                }

                PasswordEdit{
                    id: confirmpwdEdit
                    width: parent.width * 0.7
                    anchors.top: pwdEdit.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Confirm Password"
                }

                SimpleButton{
                    id: loginBtn
                    anchors.top: confirmpwdEdit.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 30
                    text: "Save"
                    color1: "#4361ee"
                    color2: "#7bdff2"
                    onClicked: {
                        console.log("Saving password")
                        //chatController.login(unameEdit.text, pwdEdit.text)
                        if (pwdEdit.text == confirmpwdEdit.text)
                        {
                            vpnmanager.resetPassword(pwdEdit.text, codeEdit.text)
                        }
                    }
                }
            }
        }
    }
}
