#include "senderthread.h"
#include "globals.h"

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QFileInfo>

SenderThread::SenderThread(QHostAddress host, const QString filePath, QObject *parent):
    QThread(parent),
    _path(filePath),
    _host(host) {
    qDebug() << filePath;
}

void SenderThread::run()
{
    QFile file(_path);
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
