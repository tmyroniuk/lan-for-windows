#include "senderthread.h"

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

SenderThread::SenderThread(QHostAddress host, quint16 port, const QString data, QObject *parent):
    QThread(parent),
    _data(data),
    _host(host),
    _port(port) {}

void SenderThread::run()
{
    QTcpSocket socket;
    socket.connectToHost(_host, _port);
    if (!socket.waitForConnected()) {
        emit error(socket.error(), socket.errorString());
        return;
    }

    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);
    stream << _data;
    socket.write(block);

    socket.disconnectFromHost();
    //TODO disconected event
    socket.waitForDisconnected();
}
