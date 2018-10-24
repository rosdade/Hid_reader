import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.0
import rosdade.ahid 1.0

Window {
    id: window
    color: "#55ffff"
    title: qsTr("USB Hid")
    width: 640
    height: 480
    visible: true
    //visibility: Window.Maximized

    AHid {
        id: ahid
    }

    TextField {
        id: textField1
        x: 27
        y: 82
        width: 200
        height: 24
        text: qsTr("")
    }

    Label {
        id: label_received_data
        x: 27
        y: 66
        text: qsTr("Received data")
    }

    Frame {
        id: frame
        x: 20
        y: 55
        width: 214
        height: 65
    }

    Button {
        id: button
        x: 27
        y: 9
        text: qsTr("START")
        onClicked: {
        }
    }
}
