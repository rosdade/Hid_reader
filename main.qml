import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.3

Window {
    id: window
    title: qsTr("USB Hid")
    width: 640
    height: 480
    color: "#87fc87"
    visible: true
    minimumWidth: 640

    Timer {
            interval: 16; running: true; repeat: true
            onTriggered: window.requestUpdate()
        }


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
        onGetParsedData: {
            realYawField.text = yaw
            realTraslField.text = trasl
        }
    }



    Rectangle {
        id: body
        color: "#dfdfdf"
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: statistics_frame.top
        anchors.left: parent.left
        anchors.topMargin: 0

        GroupBox {
            id: realPotBox
            width: 80
            height: 131
            anchors.top: parent.top
            anchors.topMargin: 25
            anchors.left: parent.left
            anchors.leftMargin: 25
            z: 1
            title: qsTr("Real POT Value")

            TextField {
                id: realYawField
                x: 0
                y: 14
                width: 56
                height: 24
                text: qsTr("")

                Label {
                    id: realYawlabel
                    x: 0
                    y: -15
                    text: qsTr("Yaw")
                }
            }

            TextField {
                id: realTraslField
                x: 0
                y: 60
                width: 56
                height: 24
                text: qsTr("")
                Label {
                    id: realTrasllabel
                    x: 0
                    y: -15
                    text: qsTr("Trasl")
                }
            }
        }
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
            width: 40
            height: 24
            text: qsTr("0")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.right: parent.right
            anchors.rightMargin: 10

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
            width: 40
            height: 24
            text: qsTr("0")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.right: textNumWritedBuffer.left
            anchors.rightMargin: 5
            Label {
                id: label_ReadedBuffer
                x: 0
                y: -15
                text: qsTr("RX/s")
            }
        }

        CheckBox {
            id: isConnected
            y: 10
            height: 24
            text: qsTr("is Connected")
            display: AbstractButton.TextBesideIcon
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.left: parent.left
            anchors.leftMargin: 0
            checked: false
            checkable: false
        }

        TextField {
            id: textReadedBuffer
            x: 66
            y: 10
            width: 200
            height: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.left: parent.left
            anchors.leftMargin: 100

            Label {
                id: label_received_data
                x: 0
                y: -15
                text: qsTr("Readed data")
            }
        }

        TextField {
            id: textWritedBuffer
            y: 10
            width: 200
            height: 24
            text: qsTr("")
            anchors.left: textReadedBuffer.right
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3

            Label {
                id: label_writed_data
                x: 0
                y: -15
                text: qsTr("Writed data")
            }
        }
    }

}

/*##^## Designer {
    D{i:6;anchors_x:253}D{i:3;anchors_x:"-5"}
}
 ##^##*/
