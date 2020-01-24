import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Universal 2.12

Rectangle {
    visible: true
    color: Universal.color(Universal.Orange)
    height: 50; width: parent.width
    radius: 10

    MouseArea {
        anchors.fill: parent
        onClicked: application.hideWindow()
    }

    Text {
        font.pointSize: 20
        anchors.centerIn: parent
        text: qsTr("Close")
        font.family: "Arial"
    }
}
