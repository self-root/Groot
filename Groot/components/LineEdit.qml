import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Item {
    id: w
    //width: parent.width * 0.7
    //property alias caption: field.placeholderText
    property alias placeholder: field.placeholderText
    property alias text: field.text
    //property alias iwidth:
    //property alias iheight: height
    implicitHeight: c.implicitHeight
    Column{
        id: c
        spacing: 0
        /**Label{
            id: label
            font.pixelSize: 11
        }**/

        TextField{
            id: field
            width: w.width
            placeholderText: "Mail/username"
        }
    }
}
