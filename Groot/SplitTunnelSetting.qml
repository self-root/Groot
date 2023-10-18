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
        text: "Split tunneling"
        color: "white"
        font.pixelSize: 18
        font.bold: true
    }

    Button{
        id: dooneBtn
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.verticalCenter: backBtn.verticalCenter
        text: "Done"
        onClicked: {
            vpnmanager.packageListModel.saveExcluded()
        }
    }

    TextField{
        id: searchPackage
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: dooneBtn.bottom
        anchors.topMargin: 6
        width: parent.width * 0.8
        height: 40
        placeholderText: "Search"
        onTextChanged: {
            var matchIndex = vpnmanager.packageListModel.search(searchPackage.text)
            console.log("Index: " + matchIndex)
            if (matchIndex > 0){
                listView.positionViewAtIndex(matchIndex,  ListView.Beginning)
            }
        }
    }

    ListView{
        id: listView
        anchors.top: searchPackage.bottom
        anchors.topMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        model: vpnmanager.packageListModel
        clip: true

        onFocusChanged: {
            if (listView.focus == true)
                searchPackage.focus = false
        }

        delegate: CheckDelegate{
            id: checkBox
            width: listView.width
            height: 45
            text: appName
            checked: excluded
            padding: 3
            onClicked: {
                vpnmanager.packageListModel.setExcluded(packageName, checkBox.checked)
            }
        }
    }
}
