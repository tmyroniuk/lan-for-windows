import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import NetApp 1.0

ListView{
    width: parent.width
    height: parent.height - 50

    model: PeerModel{
        list: peerList
    }

    delegate: Rectangle {
        id: rectangle
        width: parent.width; height: 100;

        DropArea {
            anchors.fill: parent
            enabled: true
            onEntered: {
                rectangle.color = "blue"
            }

            onExited: {
                rectangle.color = "white"
            }

            onDropped: {
                for(var i = 0; i < drop.urls.length; i++)
                    send = drop.urls[i]
            }
        }
        ColumnLayout {
            width: parent.width
            Text { font.pointSize: 20; text: name; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
            Text { font.pointSize: 14; text: address; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
        }
    }
}
