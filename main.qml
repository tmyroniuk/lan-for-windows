import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: application
    width: Screen.width / 5; height: gui.count * 100 + 50
    x: Screen.width + 2; y: 0
    color: "transparent"

    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WA_TranslucentBackground | Qt.NoDropShadowWindowHint | Qt.WindowStaysOnTopHint

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
        SpringAnimation { spring: 10; damping: 20 }
    }

    function hideWindow() {
        x = Screen.width + 2
    }

    function showWindow() {
        x = Screen.width - width
        peerList.refresh()
    }

    onClosing: {
        close.accepted = false
        application.hideWindow()
    }
}
