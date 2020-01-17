import QtQuick 2.12
import QtQuick.Window 2.12
import TrManager 1.0
import PeerModel 1.0
import QtQuick.Controls 1.6
import QtQuick.Layouts 1.12

Window {
    id: window
    width: 490
    height: 400
    visible: true
    title: qsTr("SearcherWindow")

    TrManager {
        id: trManager
    }

    ListView {
        implicitHeight: 150
        implicitWidth: 250
        clip: true

        model: PeerModel {
            id: peerModel
            list: peerList
        }

        delegate: ColumnLayout {
            width: parent.width
            Text { text: model.name }
            Text { text: model.address }
        }
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
