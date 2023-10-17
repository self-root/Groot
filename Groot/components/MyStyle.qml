import QtQuick 2.15

Item {
    property alias ifont: iconFont.name
    property string appName: "Chatterbox"
    //property alias iappleFont: appleFont.name
    FontLoader{
        id: iconFont
        source: "qrc:/assets/awesome.ttf"
    }

    /**FontLoader{
        id: appleFont
        source: "qrc:/style/Apple Color Emoji.ttf"
    }*/
}
