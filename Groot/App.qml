import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    Material.theme: Material.Dark
    Material.accent: "#4361ee"
    //anchors.fill: parent

    Connections{
        target: uicontroller
        function onToSettings(){
            viewStack.push("qrc:/SettingScreen.qml")
        }

        function onToUserAccount(){
            viewStack.push("qrc:/UserAccountScreen.qml")
        }

        function onBack(){
            viewStack.pop()
        }

        function onToSplitTunneling(){
            vpnmanager.packageListModel.getAppLists()
            viewStack.push("qrc:/SplitTunnelSetting.qml")
        }

        function onToUserAccountScreen(){
            viewStack.push("qrc:/UserAccountScreen.qml")
        }

        function onToDeviceScreen(){
            vpnmanager.getUserDevices()
            viewStack.push("qrc:/DevicesScreen.qml")
        }

        function onToAboutScreen(){
            viewStack.push("qrc:/About.qml")
        }

    }

    StackView{
        id: viewStack
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        initialItem: "qrc:/ConnectionScreen.qml"
    }

    /*SwipeView{
        id: swipeView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        ConnectionScreen{
            id: connectionScreen
        }

        UserAccountScreen{
            id: userAccountScreen
        }
    }

    footer: TabBar{
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton{
            text: "VPN"
        }

        TabButton{
            text: "Account"
        }

        onCurrentIndexChanged: {
            swipeView.currentIndex = tabBar.currentIndex
        }
    }*/
}
