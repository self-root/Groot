import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import Qt5Compat.GraphicalEffects
import "components"

Page {
    Material.theme: Material.Dark
    Material.accent: "#4361ee"

    Connections{
        target: uicontroller
        function onPwdMailRequestFail()
        {
            loginDialog.title = "Failed"
            loginDialog.text = "User does not exist"
            loginDialog.open()
        }
    }

    anchors.fill: parent

    Popup{
        id: mailDialog
        anchors.centerIn: parent
        //height: 200
        //width: 300
        //buttons: MessageDialog.Ok | MessageDialog.Cancel
        width: 250
        height: 120
        focus: true
        modal: true
        background: Rectangle{
            color: "transparent"
        }

        contentItem: Rectangle {
            id: rct
            anchors.fill: parent
            color: "#4361ee"
            radius: 20

            TextField {
                id: mailTxt
                anchors.top: parent.top
                anchors.topMargin: 6
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 12
                color: "white"
                placeholderText: "Enter email"
                Material.accent: "#ffffff"
                Material.primary: "#ffffff"
            }
            Button{
                id: okButton
                text: "Ok"
                anchors.top: mailTxt.bottom
                anchors.topMargin: 6
                anchors.horizontalCenter: parent.horizontalCenter
                Material.accent: "#ffffff"
                onClicked: {
                    vpnmanager.requestPwdResetMail(mailTxt.text)
                    mailDialog.close()
                }
            }
        }
    }

    Connections{
        target: vpnmanager

        function onLoginFailure(message){
            loginDialog.title = "Login failure";
            loginDialog.text = message
            loginDialog.open()
        }

        function onUserConflict(){
            loginDialog.title = "Conflict"
            loginDialog.text = "User already exists"
            loginDialog.open()
        }
    }

    Dialog{
        property alias text: dialogText.text
        id: loginDialog
        anchors.centerIn: parent
        Text {
            id: dialogText
            anchors.centerIn: parent
        }
    }

    ParallelAnimation{
        id: toSingUpAnimation
        running: false
        PropertyAnimation{
            target: formRect
            property: "anchors.topMargin"
            from: 150
            to: 80
            duration: 500

        }
        PropertyAnimation{
            target: signInFormRect
            property: "opacity"
            from: 1
            to: 0
            duration: 200

        }
        PropertyAnimation{
            target: signUpFormRect
            property: "opacity"
            from: 0
            to: 1
            duration: 1000
        }

        PropertyAction{
            target: welcomLbl
            property: "text"
            value: "<p>Hi</p><p>Let's get started</p>"
        }
    }

    ParallelAnimation{
        id: toSingInAnimation
        running: false
        PropertyAnimation{
            target: formRect
            property: "anchors.topMargin"
            from: 80
            to: 150
            duration: 500
        }
        PropertyAnimation{
            target: signInFormRect
            property: "opacity"
            from: 0
            to: 1
            duration: 1000
        }
        PropertyAnimation{
            target: signUpFormRect
            property: "opacity"
            from: 1
            to: 0
            duration: 200
        }


        PropertyAction{
            target: welcomLbl
            property: "text"
            value: "<p>Hi</p><p>Welcome back!</p>"
        }
    }

    Rectangle{
        id: parenFormRect
        anchors.fill: parent
        color: "#4361ee"
        Rectangle{
            id: labelRect
            width: welcomLbl.width
            height: formRect.anchors.topMargin
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            color: parent.color
            Text{
                id: welcomLbl
                anchors.left: parent.left

                anchors.verticalCenter: parent.verticalCenter
                text: "<p>Hi</p><p>Welcome back!</p>"
                color: "white"
                font.bold: true
                font.pixelSize: 25

                Behavior on font.pixelSize{
                    SmoothedAnimation{
                        duration: 600
                        velocity: SmoothedAnimation.Sync
                    }
                }
            }
        }


        Rectangle{
            id: formRect
            anchors.top: parent.top
            width: parent.width
            anchors.topMargin: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -40
            color: "#1b1b1b"
            radius: 40
            Rectangle{
                id: signInFormRect
                visible: opacity > 0? true : false
                opacity: 1
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 42
                color: parent.color

                LineEdit{
                    id: unameEdit
                    width: parent.width * 0.7
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Email"
                }

                PasswordEdit{
                    id: pwdEdit
                    width: parent.width * 0.7
                    anchors.top: unameEdit.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Password"
                }

                SimpleButton{
                    id: loginBtn
                    anchors.top: pwdEdit.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 30
                    text: "Log in"
                    color1: "#4361ee"
                    color2: "#7bdff2"
                    onClicked: {
                        console.log("Log in...")
                        //chatController.login(unameEdit.text, pwdEdit.text)
                        vpnmanager.login(unameEdit.text, pwdEdit.text)
                    }
                }

                Rectangle{
                    anchors.top: loginBtn.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    anchors.topMargin: 10
                    Text{
                        id: goSignup
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "<p><font color='#ffffff'>Don't have an account?</font><font color='#4361ee'> <a href='#'> Sign up</a></font></p>"
                        onLinkActivated: {
                            console.log("User wants to sign up")
                            toSingUpAnimation.running = true
                            welcomLbl.font.pixelSize = 20
                        }

                    }
                    Text{
                        id: goReset
                        anchors.top: goSignup.bottom
                        anchors.topMargin: 4
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "<p><font color='#ffffff'>Forgot password?</font><font color='#4361ee'> <a href='#'> Reset password</a></font></p>"
                        onLinkActivated: {
                            console.log("reset")
                            mailDialog.open()
                        }

                        /*MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                console.log("User wants to sign up")
                                toSingUpAnimation.running = true
                                welcomLbl.font.pixelSize = 20
                            }
                        }*/
                    }
                    /*Label{
                        id: lbl
                        text: "Don't have an account?"
                    }*

                    /*Text{
                        id: lbl2
                        anchors.left: lbl.right
                        anchors.leftMargin: 6
                        font.underline: true
                        text: "Sign up"
                        color: "#4361ee"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                console.log("User wants to sign up")
                                toSingUpAnimation.running = true
                                welcomLbl.font.pixelSize = 20
                            }
                        }
                    }

                    Label{
                        id: llb
                        anchors.top: lbl.bottom
                        anchors.topMargin: 5
                        text: "Forgot password?"
                    }

                    Text{
                        id: llbl2
                        anchors.left: llb.right
                        anchors.leftMargin: 6
                        anchors.top: lbl2.bottom
                        anchors.topMargin: 5
                        font.underline: true
                        text: "Reset password"
                        color: "#4361ee"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                mailDialog.open()
                            }
                        }

                    }*/
                }
            }

            Rectangle{
                id: signUpFormRect
                visible: opacity > 0? true : false
                opacity: 0
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 42
                color: parent.color

                LineEdit{
                    id: singUpMail
                    width: parent.width * 0.7
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Email"
                }

                PasswordEdit{
                    id: signUpPwd
                    width: parent.width * 0.7
                    anchors.top: singUpMail.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Password"
                }
                PasswordEdit{
                    id: signUpPwdConf
                    width: parent.width * 0.7
                    anchors.top: signUpPwd.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholder: "Confirm password"
                }
                SimpleButton{
                    id: signUpBtn
                    anchors.top: signUpPwdConf.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Create an account"
                    color1: "#4361ee"
                    color2: "#7bdff2"
                    onClicked: {
                        vpnmanager.signup(singUpMail.text, signUpPwd.text)
                    }
                }

                Rectangle{
                    anchors.top: signUpBtn.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: lblSingUp.width + lblSingUp2.width
                    anchors.topMargin: 10
                    Label{
                        id: lblSingUp
                        text: "Already have an account?"
                    }

                    Text{
                        id: lblSingUp2
                        anchors.left: lblSingUp.right
                        anchors.leftMargin: 6
                        font.underline: true
                        text: "Sign in"
                        color: "#4361ee"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                console.log("User wants to sign in")
                                toSingInAnimation.running = true
                                welcomLbl.font.pixelSize = 25
                            }
                        }
                    }
                }
            }
        }
    }

}
