import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1

ApplicationWindow {
    id: application
    width: Screen.width / 5; height: Screen.height / 2
    x: Screen.width - width; y: 0
    visible: true
    flags: Qt.Popup | Qt.NoDropShadowWindowHint

    AppGui {
        anchors.centerIn: parent
    }

    SystemTrayIcon {
        visible: true
        iconSource: "qrc:/ico/QCicon.png"
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }
    onClosing: {
        close.accepted = false
        application.hide()
    }
}
