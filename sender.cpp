#include "sender.h"

Sender::Sender(QHostAddress host, const QString filePath, QObject *parent) :
    QObject(parent),
    _filePath(filePath),
    _host(host) {}

void Sender::startTransmission()
{
    QFile file(_filePath);
    if(file.open(QIODevice::ReadOnly)){
        QTcpSocket socket;
        socket.connectToHost(_host, TCP_PORT);
        if (!socket.waitForConnected()) {
            emit socketError(socket.error(), socket.errorString());
            return;
        }
        //sending data
        QByteArray block;
        QDataStream wrightStream(&block, QIODevice::WriteOnly);
        wrightStream.setVersion(QDataStream::Qt_5_12);
        wrightStream << QFileInfo(file).fileName();
        wrightStream << file.size();
        socket.write(block);
        //Sending file
        while(!file.atEnd()){
            block = file.read(BLOCK_LEN);
            socket.write(block);
        }
        socket.disconnectFromHost();
        socket.waitForDisconnected();
        file.close();
    }
    else {
        qDebug() << "sender cant open";
        emit fileError(file.error(), file.errorString());
    }
}
