import QtQuick 2.12
import QtQuick.Window 2.12
import SocketQML.peermanager 1.0
import QtQuick.Controls 1.6

Window {
    id: window
    width: 490
    height: 400
    visible: true
    title: qsTr("SearcherWindow")

    PeerManager{
        id: manager
    }

    TextInput {
        id: textInput
        y: 0
        height: 45
        text: qsTr("")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        font.pixelSize: 16
    }

    Button {
        id: send
        x: 69
        y: 62
        text: qsTr("SEND")
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: manager.refresh()
    }
}
