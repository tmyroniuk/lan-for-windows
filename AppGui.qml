import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


import NetApp 1.0

Frame {
    anchors.fill: parent
    ListView{

        anchors.fill: parent
        clip: true

        model: PeerModel{
            list: peerList
        }

        delegate: Rectangle {
            id: rectangle
            width: parent.width
            color: "cyan"; height: 100;

            DropArea {
                anchors.fill: parent
                enabled: true
                onEntered: {
                    rectangle.color = "blue"
                    console.log("entered")
                }

                onExited: {
                    rectangle.color = "cyan"
                    console.log("exited")
                }

                onDropped: {
                    for(var i = 0; i < drop.urls.length; i++) {
                        console.log(drop.urls[i])
                        send = drop.urls[i]
                    }
                }
            }
            ColumnLayout {
                width: parent.width
                Layout.alignment: Qt.AlignHCenter

                Text { font.pointSize: 20; text: name; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
                Text { font.pointSize: 14; text: address; fontSizeMode: Text.Fit; horizontalAlignment: Text.AlignHCenter }
            }
        }
    }
}
