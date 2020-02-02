import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import NetApp 1.0

ApplicationWindow {
    id: application
    width: 400; height: gui.count * 120 + 170
    x: Screen.width + 2; y: Screen.height / 12
    color: "transparent"

    flags: Qt.Popup | Qt.NoDropShadowWindowHint | Qt.WindowStaysOnTopHint

    visible: x >= Screen.width ? false : true

    InListControl { id: control; anchors.top: application.top }

    AppGui { id: gui; anchors.top: control.bottom }

    Connections {
        target: TrManager
        function onComplete(fileName) {
            trayIcon.showMessage("Success", fileName)
        }

        function onError(fileName, errorString) {
            trayIcon.showMessage("Success", fileName + errorString)
        }
    }

    TrayIcon {
        id: trayIcon
    }

    Behavior on x {
        SpringAnimation { spring: 8; damping: 10 }
    }

    function hideWindow() {
        x = Screen.width + 2
    }

    function showWindow() {
        trManager.refresh()
        x = Screen.width - width
    }

    onClosing: {
        close.accepted = false
        application.hideWindow()
    }
}
