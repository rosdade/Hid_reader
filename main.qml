import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    color: "#aa0000"
    visible: true
    title: qsTr("Hello World")

    TextEdit {
        id: textEdit
        x: 72
        y: 132
        width: 80
        height: 20
        text: qsTr("Text Edit")
        font.pixelSize: 12
    }

    TextInput {
        id: textInput
        x: 72
        y: 195
        width: 80
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
