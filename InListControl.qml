import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    visible: true
    color: "orange"
    height: 50; width: parent.width

    MouseArea {
        anchors.fill: parent
        onClicked: application.hideWindow()
    }
}
