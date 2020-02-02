import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import NetApp 1.0

ListView{
    width: parent.width
    height: parent.height
    spacing: 20

    anchors {
        topMargin: 20
        top: control.botom
    }

    populate: Transition {
        NumberAnimation { property: "x"; from: x + width + 2; duration: 200 }
    }

    model: PeerModel{
        id: peerModel
        manager: trManager
    }

    delegate: ColumnLayout {
        id: myDelegate
        //height: peerRect.height + transmissionList.height
        width: parent.width
        spacing: 0

        Rectangle {
            id: peerRect
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

            Text {
                anchors.top: peerRect.top
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
                width: parent.width
                text: name
                padding: 5
                font.pixelSize: 40
            }
            Text {
                anchors.bottom: peerRect.bottom
                font.pixelSize: 20
                width: parent.width
                text: address
                padding: 10
                horizontalAlignment: Text.AlignHCenter
            }
        }
        ListView {
            id: transmissionList
            width: parent.width
            height: count * 50
            spacing: 0
            model: TransmissionModel { peerPtr: peer }

            delegate: Item {
                height: 50
                width: parent.width
                ProgressBar {
                    id: bar
                    anchors.fill: parent
                    value: progress

                    background: Rectangle {
                        implicitWidth: parent.width
                        implicitHeight: parent.height
                        color: Material.color(Material.Gray , Material.ShadeA400)
                    }

                    contentItem: Rectangle {
                        width: bar.visualPosition * parent.width
                        height: parent.height
                        color: Material.color(Material.Green)

                    }
                }
                Text {
                    anchors.fill: parent
                    text: fileName
                    font.pixelSize: 24
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
