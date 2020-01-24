import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
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
        NumberAnimation { property: "x"; from: x + width + 2; duration: 200 }
    }

    model: PeerModel{
        list: peerList
    }

    delegate: Rectangle {
        id: rectangle
        width: parent.width
        height: 100

        color: (index & 1) ? Material.color(Material.Yellow, Material.Shade400) : Material.color(Material.Blue, Material.Shade400)
        border.color: Material.color(Material.Cyan, Material.ShadeA100)
        border.width: droper.containsDrag ? 5 : 0
        radius: 4

        DropArea {
            id: droper
            anchors.fill: parent
            enabled: true

            onDropped: {
                for(var i = 0; i < drop.urls.length; i++)
                    send = drop.urls[i]
            }
        }

        ColumnLayout {
            width: parent.width
            Text {
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                Layout.preferredWidth: parent.width
                text: name
                padding: 5
                font.pixelSize: 40
            }
            Text {
                font.pixelSize: 20; Layout.preferredWidth: parent.width; text: address; padding: 10; horizontalAlignment: Text.AlignHCenter}
        }
    }
}
