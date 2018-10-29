import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.3

Window {
    id: window
    color: "#55ffff"
    title: qsTr("USB Hid")
    width: 640
    height: 480
    visible: true
    minimumWidth: 640
    //visibility: Window.Maximized

    Connections {
        target: usbIO
        onReadedBuffer: {
            textReadedBuffer.text = buffer
        }
        onWritedBuffer: {
            textWritedBuffer.text = buffer
        }
        onUsbConnected: {
            isConnected.checked = status
        }
        onGetStatistics: {
            textNumReadBuffer.text = n_in
            textNumWritedBuffer.text = n_out
        }
    }

    Frame {
        id: frame
        width: 640
        height: 65
        transformOrigin: Item.Center
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0


        TextField {
            id: textReadedBuffer
            x: -5
            y: 15
            width: 621
            height: 24
            text: qsTr("")

            Label {
                id: label_received_data
                x: 0
                y: -15
                text: qsTr("Readed data")
            }
        }
    }

    Frame {
        id: frame1
        width: 640
        height: 65
        topPadding: 12
        TextField {
            id: textWritedBuffer
            x: -5
            y: 15
            width: 621
            height: 24
            text: qsTr("")

            Label {
                id: label_writed_data
                x: 0
                y: -15
                text: qsTr("Writed data")
            }
        }
        anchors.left: parent.left
        anchors.top: frame.bottom
        anchors.topMargin: 0
        anchors.leftMargin: 0
        transformOrigin: Item.Center
    }

    Frame {
        id: statistics_frame
        y: 345
        width: 640
        height: 55
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        TextField {
            id: textNumWritedBuffer
            x: 500
            y: 10
            width: 70
            height: 24
            text: qsTr("0")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.right: parent.right
            anchors.rightMargin: 46

            Label {
                id: label_writedBuffer
                x: 0
                y: -15
                text: qsTr("Tx/s")
            }
        }

        TextField {
            id: textNumReadBuffer
            x: 503
            y: 10
            width: 70
            height: 24
            text: qsTr("0")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.right: textNumWritedBuffer.left
            anchors.rightMargin: 10
            Label {
                id: label_ReadedBuffer
                x: 0
                y: -15
                text: qsTr("RX/s")
            }
        }

        CheckBox {
            id: isConnected
            y: 0
            text: qsTr("is Connected")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -9
            anchors.left: parent.left
            anchors.leftMargin: 0
            checked: false
            checkable: false
        }
    }





}
