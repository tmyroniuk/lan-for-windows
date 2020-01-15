import QtQuick 2.12
import QtQuick.Window 2.12
import SocketQML.transmissionmanager 1.0
import QtQuick.Controls 1.6

Window {
    id: window
    width: 490
    height: 400
    visible: true
    title: qsTr("SearcherWindow")

    TrManager{
        id: trManager
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        enabled: true

        onDropped: {
            for(var i = 0; i < drop.urls.length; i++)
                trManager.sendToLaptop(drop.urls[i])
        }
    }
}
