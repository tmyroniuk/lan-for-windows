import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: application
    width: 400; height: gui.count * 120 + 170
    x: Screen.width + 2; y: Screen.height / 12
    color: "transparent"

    flags: Qt.Popup | Qt.NoDropShadowWindowHint | Qt.WindowStaysOnTopHint

    visible: x >= Screen.width ? false : true

    InListControl {
        id: control
        anchors.top: application.top
    }

    AppGui {
        id: gui
        anchors.top: control.bottom
    }

    TrayControl {}

    Behavior on x {
        SpringAnimation { spring: 8; damping: 10 }
    }

    function hideWindow() {
        x = Screen.width + 2
    }

    function showWindow() {
        peerList.clear()
        x = Screen.width - width
        peerList.refresh()
    }

    onClosing: {
        close.accepted = false
        application.hideWindow()
    }
}
