import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Universal 2.12
import QtQuick.Layouts 1.12

import NetApp 1.0

ListView{
    width: parent.width
    height: parent.height - 50
    spacing: 20

    anchors {
        topMargin: 20
        top: control.botom
    }

    populate: Transition {
        SpringAnimation { property: "x"; from: x + width; to: x; spring: 8; damping: 10 }
    }

    model: PeerModel{
        list: peerList
    }

    delegate: Rectangle {
        id: rectangle
        width: parent.width; height: 100;
        color: Universal.color(Universal.Steel)
        border.color: Universal.color(Universal.Cobalt)
        radius: 10

        DropArea {
            anchors.fill: parent
            enabled: true
            onEntered: {
                rectangle.border.width = 5
            }

            onExited: {
                rectangle.border.width = 0
            }

            onDropped: {
                rectangle.border.width = 0
                for(var i = 0; i < drop.urls.length; i++)
                    send = drop.urls[i]
            }
        }
        ColumnLayout {
            width: parent.width
            Text { font.pointSize: 20; width: parent.width; text: name; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
            Text { font.pointSize: 14; width: parent.width; text: address; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
        }
    }
}
