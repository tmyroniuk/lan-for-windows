import QtQuick 2.12
import Qt.labs.platform 1.1

SystemTrayIcon {
    visible: true
    iconSource: "qrc:/ico/QCicon.png"

    menu: Menu {
        MenuItem {
            text: qsTr("Quit")
            onTriggered: {
                hide()
                Qt.callLater(Qt.quit)
            }
        }
    }

    onActivated: {
        if(reason === SystemTrayIcon.Trigger)
            (application.visible) ? application.hideWindow() : application.showWindow()
    }
}
